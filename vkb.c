/* copyright 2013 Citrix
 * author Vincent Hanquez
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <webkit/webkit.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <X11/keysymdef.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <X11/Xos.h>
#include <X11/Xproto.h>

#include "socket.h"

#define KBD_HTML "vkb.html"

#define USE_UNIX_SOCKET_NOTIFICATION

Display *xdisp;
int max_keycode, min_keycode;
int screen_nb = 0;

static Atom Atom_VKB_IM_INVOKER_COMMAND;

struct { char *name; int keycode; char *unic;} special_keys[] = {
	{ "Enter", XK_Return, NULL},
	{ "Backspace", XK_BackSpace, NULL },
	{ "Bksp", XK_BackSpace, NULL },
	{ "Tab", XK_Tab, NULL },
	{ "Space", 0, " " },
	{ "%%E9", 0, "é" },
	{ "%%C9", 0, "É" },
	{ "%%FA", 0, "ć" },
	{ NULL, 0, NULL }
};

static void xkey_press_keycode(KeyCode keycode)
{
	//printf("sending event\n");
	XTestFakeKeyEvent(xdisp, keycode, 1, CurrentTime);
	//XSync(xdisp, False);
	XTestFakeKeyEvent(xdisp, keycode, 0, CurrentTime);
	XSync(xdisp, False);
}

static void xkey_press_sym(KeySym keysym)
{
	KeyCode code = 0;
	
	code = XKeysymToKeycode(xdisp, keysym);
	if (!code) {
		printf("oops no keycode found\n");
		return;
	}
	xkey_press_keycode(code);
}

static void xkey_press_char(const char *buf)
{
	char c = buf[0];
	uint32_t utf32;
	int i;

	for (i = 0; 1; i++) {
		if (!special_keys[i].name)
			break;
		if (strcmp(special_keys[i].name, buf) == 0) {
			xkey_press_sym(special_keys[i].keycode);
			return;
		}
	}
	if (c > 0x7f) {
		printf("unicode not implemented\n");
		return;
	}
	utf32 = c;
	//printf("utf32: %x\n", utf32);
	xkey_press_sym(utf32);
}

static void move_window(GtkWindow *window)
{
	GdkDisplay *display;
	GdkScreen *screen;
	GdkRectangle geometry;

	display = gdk_display_get_default();
	screen  = gdk_display_get_screen(display, 0);
	gdk_screen_get_monitor_geometry(screen, screen_nb, &geometry);
	printf("geometry: x: %d  y: %d  w: %d  h: %d\n",
		geometry.x, geometry.y, geometry.width, geometry.height);

	gtk_window_set_default_size(window, geometry.width, 260);
	gtk_window_move(window, geometry.x, geometry.height - 260);
}

static void destroy_window_cb(GtkWidget* widget, GtkWidget* window)
{
	gtk_main_quit();
}

static gboolean close_webview_cb(WebKitWebView* webView, GtkWidget* window)
{
	gtk_widget_destroy(window);
	return TRUE;
}

static gboolean navigation_cb(WebKitWebView             *web_view,
                              WebKitWebFrame            *frame,
                              WebKitNetworkRequest      *request,
                              WebKitWebNavigationAction *navigation_action,
                              WebKitWebPolicyDecision   *policy_decision,
                              gpointer                   user_data)
{
	const char *uri;
	char *pwd;
	char path[1024];

	uri = webkit_network_request_get_uri(request);
	pwd = getenv("PWD");
        snprintf(path, 1024, "file://%s/%s", pwd, KBD_HTML);

	if (strncmp(uri, path, strlen(path)) == 0) {
		uri += strlen(path);
		if (strncmp(uri, "#key_exit", 9) == 0)
			gtk_main_quit();
		else if (strncmp(uri, "#key_", 5) == 0) {
			printf("key: %s\n", uri + 5);
			webkit_web_policy_decision_ignore(policy_decision);
			xkey_press_char(uri + 5);
		} else
			webkit_web_policy_decision_use(policy_decision);
		return TRUE;
	}
	printf("navigation requested: %s\n", uri);
	webkit_web_policy_decision_ignore(policy_decision);
	return TRUE;
}

static gboolean download_request_cb(WebKitWebView  *web_view,
                                    WebKitDownload *download,
				    gpointer        user_data)
{
	const char *uri;
	uri = webkit_download_get_destination_uri(download);
	printf("download request: %s\n", uri);
	webkit_download_cancel(download);
	return TRUE;
}

static void resource_request_cb(WebKitWebView         *web_view,
                                WebKitWebFrame        *web_frame,
                                WebKitWebResource     *web_resource,
                                WebKitNetworkRequest  *request,
                                WebKitNetworkResponse *response,
                                gpointer               user_data) 
{
}

struct load_uri_cb
{
	GtkWidget *main_window;
	WebKitWebView *webView;
	char *path;
};

static gboolean notification_read(GIOChannel *src, GIOCondition cond, gpointer data)
{
	char buf[1];
	gsize read;
	struct load_uri_cb *cbdata = (struct load_uri_cb *) data;
	GtkWidget *main_window = cbdata->main_window;

	buf[0] = '\0';
	g_io_channel_read_chars(src, buf, 1, &read, NULL);

	if (read == 1) {
		switch (buf[0]) {
		case 0x29:
			//printf("POP UP\n");
			gtk_widget_show_all(main_window);
			break;
		case 0x39:
			//printf("POP OUT\n");
			gtk_widget_hide(main_window);
			break;
		default:
			//printf("read : %x\n", buf[0]);
			break;
		}
	}
	g_io_channel_shutdown(src, true, NULL);
	return FALSE;
}

static gboolean notification_accept(GIOChannel *src, GIOCondition cond, gpointer data)
{
	int fd;
	struct sockaddr_un addr;
	socklen_t addrlen;
	GIOChannel *channel;

	//printf("notification_accept: %d (out=%d,in=%d,hup=%d,pri=%d)\n", cond, G_IO_OUT, G_IO_IN, G_IO_HUP, G_IO_PRI);

	fd = accept(g_io_channel_unix_get_fd(src), (struct sockaddr *) &addr, &addrlen);
	//printf("accepted: %d\n", fd);

	channel = g_io_channel_unix_new(fd);
	g_io_add_watch(channel, G_IO_IN, notification_read, data);

	return TRUE;
}

static gboolean timeouted(void *stuff)
{
#ifdef USE_UNIX_SOCKET_NOTIFICATION
	int fd;
	GIOChannel *channel;
#endif
	struct load_uri_cb *cbdata = (struct load_uri_cb *) stuff;
	webkit_web_view_load_uri(cbdata->webView, cbdata->path);

#ifdef USE_UNIX_SOCKET_NOTIFICATION
	fd = vkb_notification_listen();
	if (fd == -1) {
		printf("cannot create notification channel\n");
		exit(2);
	}
	channel = g_io_channel_unix_new(fd);
	g_io_add_watch(channel, G_IO_IN | G_IO_HUP, notification_accept, cbdata);
#endif
	return FALSE;
}

static GdkFilterReturn filter_event(GdkXEvent *xev, GdkEvent *event, gpointer data)
{
	XEvent *xevent = (GdkXEvent *)xev;
	//printf("xevent->type = %d (%d)\n", xevent->type, ClientMessage);
	if (xevent->type == ClientMessage) {
		switch (xevent->xclient.data.l[0]) {
		case 0x2901:
			printf("POP IN\n");
			/* show keyboard */
			break;
		case 0x2902:
			printf("POP OUT\n");
			/* hide keyboard */
			break;
		}
		return GDK_FILTER_REMOVE;
	}
	return GDK_FILTER_CONTINUE;
}

static void set_no_focus(GdkWindow *window)
{
	Window xwin;
	XWMHints *wm_hints;

#if GTK_MAJOR_VERSION == 3
	xwin = gdk_x11_window_get_xid(window);
#else
	xwin = gdk_x11_drawable_get_xid(window);
#endif
	wm_hints = XAllocWMHints();
	if (!wm_hints) {
		printf("cannot set no focus hint\n");
		exit(1);
	}

	wm_hints->input = False;
	wm_hints->flags = InputHint;
	XSetWMHints(xdisp, xwin, wm_hints);
	XFree(wm_hints);

	gdk_window_add_filter(window, filter_event, NULL);
}

int main(int argc, char **argv)
{
	char *pwd;
	char path[1024];
	int event, error, major, minor;
	//int event, error, major, minor, n_keysyms_per_keycode;
	GdkDisplay *display;
	//KeySym *keysyms;
	WebKitWebSettings *settings;
	struct load_uri_cb cbdata;
	
	if (argc > 1) {
		screen_nb = atoi(argv[1]);
	}

	pwd = getenv("PWD");
	snprintf(path, 1024, "file://%s/%s", pwd, KBD_HTML);

	gtk_init(&argc, &argv);


	display = gdk_display_get_default();
	xdisp = gdk_x11_display_get_xdisplay(display);

	if (!XTestQueryExtension(xdisp, &event, &error, &major, &minor)) {
		printf("x test query extension not supported\n");
		exit(1);
	}

	Atom_VKB_IM_INVOKER_COMMAND = XInternAtom(xdisp, "_VKB_IM_INVOKER_COMMAND", False);

	//XDisplayKeycodes(xdisp, &min_keycode, &max_keycode);
	//keysyms = XGetKeyboardMapping(xdisp, min_keycode, max_keycode - min_keycode + 1, &n_keysyms_per_keycode);

	GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_type_hint(GTK_WINDOW(main_window), GDK_WINDOW_TYPE_HINT_DOCK);

	move_window(GTK_WINDOW(main_window));

	WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
	settings = webkit_web_view_get_settings(webView);
	g_object_set(settings, "enable-file-access-from-file-uris", TRUE, NULL);

	g_signal_connect(main_window, "destroy", G_CALLBACK(destroy_window_cb), NULL);
	g_signal_connect(webView, "close-web-view", G_CALLBACK(close_webview_cb), main_window);
	g_signal_connect(webView, "navigation-policy-decision-requested", G_CALLBACK(navigation_cb), NULL);
	g_signal_connect(webView, "resource-request-starting", G_CALLBACK(resource_request_cb), NULL);

	g_signal_connect(webView, "download-requested", G_CALLBACK(download_request_cb), NULL);

	gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));


	gtk_widget_grab_focus(GTK_WIDGET(webView));
	gtk_widget_add_events(main_window, GDK_CLIENT_EVENT | GDK_PROPERTY_CHANGE_MASK | GDK_STRUCTURE_MASK);

	gtk_widget_realize(main_window);
	//gtk_widget_show_all(main_window);

	set_no_focus(gtk_widget_get_window(main_window));

	cbdata.webView = webView;
	cbdata.path = path;
	cbdata.main_window = main_window;
	g_timeout_add(100, timeouted, &cbdata);

	webkit_web_view_set_full_content_zoom(webView, TRUE);
	webkit_web_view_set_zoom_level(webView, 0.9);

	gtk_main();

	return 0;
}


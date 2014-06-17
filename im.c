/*
 * Copyright (c) 2013 Citrix Systems, Inc.
 * 
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

#include <gtk/gtkimmodule.h>
#include <gtk/gtkimcontextsimple.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "socket.h"

#define IM_CONTEXT "vkb"

static GtkIMContextClass *parent_class;
static GType im_context_type = 0;

typedef struct { GtkIMContextSimple context; } VkbIMContext;
typedef struct { GtkIMContextSimpleClass parent_class; } VkbIMContextClass;

static const GtkIMContextInfo im_info = {
	IM_CONTEXT, "Citrix Awesome Screen Keyboard", "", "", "*"
};

static const GtkIMContextInfo *info_list[] = { &im_info };

void im_module_list(const GtkIMContextInfo ***contexts, guint *n_contexts)
{
	*contexts = info_list;
	*n_contexts = G_N_ELEMENTS(info_list);
}

static void send_focus_event(int ev)
{
	int fd;
	char buf[1];

	fd = vkb_notification_connect();
	if (fd == -1)
		return;
	buf[0] = ev;
	write(fd, buf, 1);
	close(fd);
}

static void im_context_focus_in(GtkIMContext *context)
{
	send_focus_event(0x29);
	if (GTK_IM_CONTEXT_CLASS(parent_class)->focus_in)
		GTK_IM_CONTEXT_CLASS(parent_class)->focus_in (context);
}

static void im_context_focus_out(GtkIMContext *context)
{
	send_focus_event(0x39);
	if (GTK_IM_CONTEXT_CLASS (parent_class)->focus_out)
		GTK_IM_CONTEXT_CLASS (parent_class)->focus_out(context);
}

static void im_context_class_init(VkbIMContextClass *klass)
{
	GtkIMContextClass *context_class = GTK_IM_CONTEXT_CLASS(klass);
	parent_class = g_type_class_peek_parent(klass);
	context_class->focus_in = im_context_focus_in;
	context_class->focus_out = im_context_focus_out;
}

void im_context_init(VkbIMContext *self)
{
}

void im_module_init(GTypeModule *module)
{
	static const GTypeInfo im_context_info = {
		sizeof (VkbIMContextClass),
		NULL,
		NULL,
		(GClassInitFunc) im_context_class_init,
		NULL,
		NULL,
		sizeof (VkbIMContext),
		0,
		(GInstanceInitFunc) im_context_init,
	};

	if (im_context_type)
		return;
	im_context_type = g_type_module_register_type(module, GTK_TYPE_IM_CONTEXT_SIMPLE, "VkbIMContext", &im_context_info, 0);
}

void im_module_exit()
{
}

GtkIMContext * im_module_create(const char *context_id)
{
	if (strcmp(context_id, IM_CONTEXT) != 0)
		return NULL;
	return g_object_new(im_context_type, NULL);
}

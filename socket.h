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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/vkb_notification"

static int vkb_notification_socket_addr(struct sockaddr_un *un)
{
	un->sun_family = AF_UNIX;
	memcpy(un->sun_path, SOCKET_PATH, sizeof(SOCKET_PATH));
	return 0;
}

int vkb_notification_listen(void)
{
	struct sockaddr_un un;
	int s;

	vkb_notification_socket_addr(&un);

	unlink(SOCKET_PATH);
	s = socket(AF_UNIX, SOCK_STREAM, 0);
	if (s == -1) {
		printf("notification listen failed\n");
		return -1;
	}

	if (bind(s, (struct sockaddr *) &un, sizeof(struct sockaddr_un)) == -1) {
		close(s);
		printf("notification bind failed\n");
		return -1;
	}

	if (listen(s, 2) == -1) {
		close(s);
		printf("error\n");
	}

	return s;
}

int vkb_notification_connect(void)
{
	struct sockaddr_un un;
	int s;

	vkb_notification_socket_addr(&un);
	s = socket(AF_UNIX, SOCK_STREAM, 0);
	if (s == -1) {
		printf("notification_connect failed\n");
	}

	if (connect(s, (struct sockaddr *) &un, sizeof(struct sockaddr_un)) == -1) {
		perror("notification connect");
		return -1;
	}
	return s;
}

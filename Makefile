#
# Copyright (c) 2013 Citrix Systems, Inc.
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

CFLAGS = -Wall

all: vkb libvkb-im-invoker.so

vkb: vkb.c
	$(CC) $(CFLAGS) $< -o $@ `pkg-config --cflags --libs x11 xtst gdk-x11-2.0 gtk+-2.0 webkit-1.0`

libvkb-im-invoker.so: im.c
	$(CC) -fPIC $(CFLAGS) -c -o im.o im.c `pkg-config --cflags --libs x11 xtst gdk-x11-2.0 gtk+-2.0`
	$(CC) -shared -fPIC -DPIC -Wl,-soname -Wl,libvkb-im-invoker.so -o $@ im.o

.PHONY: clean
clean:
	rm vkb im.o libvkb-im-invoker.so

install:
	install -m 0755 -d ${DESTDIR}
	install -m 0644 vkb \
			libvkb-im-invoker.so \
			vkb.html \
			vkb.css \
			vkb.js \
			${DESTDIR}


libcaja-kill-thumbs.so: libcaja-kill-thumbs.c
	gcc libcaja-kill-thumbs.c -shared -fPIC -o libcaja-kill-thumbs.so \
		-I/usr/include/caja `pkg-config --libs --cflags gtk+-2.0`

install:
	cp libcaja-kill-thumbs.caja-extension /usr/share/caja/extensions/
	cp libcaja-kill-thumbs.so /usr/lib/caja/extensions-2.0/

uninstall:
	if [ -f /usr/share/caja/extensions/libcaja-kill-thumbs.caja-extension ]; then \
		rm /usr/share/caja/extensions/libcaja-kill-thumbs.caja-extension; \
	fi;
	if [ -f /usr/lib/caja/extensions-2.0/libcaja-kill-thumbs.so ]; then \
		rm /usr/lib/caja/extensions-2.0/libcaja-kill-thumbs.so; \
	fi;

clean:
	if [ -f libcaja-kill-thumbs.so ]; then rm libcaja-kill-thumbs.so; fi;

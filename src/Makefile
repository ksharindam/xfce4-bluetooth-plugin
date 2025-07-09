MODULE = bluetooth
LIBDIR = /usr/lib/x86_64-linux-gnu
PLUGIN_DIR = $(LIBDIR)/xfce4/panel/plugins
DESKTOP_DIR = /usr/share/xfce4/panel/plugins
DESTDIR =
CFLAGS = `pkg-config --cflags --libs libxfce4panel-2.0` -DLXPLUG -Wl,-rpath=$(LIBDIR) -shared -fPIC -Wall
all:
	gcc -o lib$(MODULE).so $(CFLAGS) $(MODULE).c lxpanel-compat.c
	
clean:
	rm -f lib$(MODULE).so

install:
	install lib$(MODULE).so $(PLUGIN_DIR)
	install ../data/$(MODULE).desktop $(DESKTOP_DIR)
	install -D ../data/lxplug-bluetooth.ui $(DESKTOP_DIR)/../ui/lxplug-bluetooth.ui

uninstall:
	rm $(PLUGIN_DIR)/lib$(MODULE).so $(DESKTOP_DIR)/$(MODULE).desktop $(DESKTOP_DIR)/../ui/lxplug-bluetooth.ui
	find $(DESKTOP_DIR)/.. -type d -empty -delete

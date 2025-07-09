#pragma once
#include <libxfce4panel/libxfce4panel.h>

void xfce_panel_plugin_set_taskbar_icon(XfcePanelPlugin *plugin,
                                        GtkWidget *image, const char *name);

void xfce_panel_plugin_set_menu_icon(XfcePanelPlugin *plugin,
                                        GtkWidget *image, const char *name);


/*void xfce_panel_plugin_popup_set_position_helper(XfcePanelPlugin *plugin,
                    GtkWidget *attach_to, GtkWidget *popup, int *x, int *y);*/

void xfce_panel_plugin_popup_at_button(XfcePanelPlugin *panel, GtkWidget *window, GtkWidget *button, gpointer userdata);

GtkWidget* xfce_panel_plugin_new_menu_item (XfcePanelPlugin *p,
                        const char *text, int maxlen, const char *iconname);


void xfce_panel_plugin_update_menu_icon (GtkWidget *item, GtkWidget *image);

const char* wrap_get_menu_label(GtkWidget *item);


// lxpanel api
#define lxpanel_plugin_set_data(plugin,data,destructor) \
        g_object_set_data(G_OBJECT(plugin),"plugin-data",data)

#define lxpanel_plugin_get_data(plugin) \
        g_object_get_data(G_OBJECT(plugin),"plugin-data")

#define lxpanel_plugin_update_menu_icon(item,image) \
        xfce_panel_plugin_update_menu_icon(item,image)

#define wrap_set_taskbar_icon(data,image,icon_name) \
        xfce_panel_plugin_set_taskbar_icon(data->panel,image,icon_name)

#define wrap_new_menu_item(data,text,maxlen,iconname) \
        xfce_panel_plugin_new_menu_item(data->panel,text,maxlen,iconname)

#define wrap_set_menu_icon(data,image,name) \
        xfce_panel_plugin_set_menu_icon(data->panel,image,name)

const char* wrap_get_menu_label(GtkWidget *item);


#define wrap_show_menu(plugin,menu) gtk_menu_popup_at_widget(GTK_MENU(menu),plugin,GDK_GRAVITY_SOUTH_WEST,GDK_GRAVITY_NORTH_WEST,NULL)

#define wrap_popup_at_button(data,window,button) xfce_panel_plugin_popup_at_button(data->panel,window,button,data)

#define MENU_ICON_SPACE 6
// does nothing
#define CHECK_LONGPRESS
// disable translations (you must comment out <glib/gprintf.h>)
#define _

#define PACKAGE_DATA_DIR "/usr/share/xfce4/panel"

#define textdomain(x)

#define LXPanel XfcePanelPlugin



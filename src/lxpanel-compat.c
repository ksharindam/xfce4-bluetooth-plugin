#include <string.h>
#include "plugin.h"
// xfce panel : https://github.com/raboof/xfce4-panel/tree/master/libxfce4panel
// lxpanel : https://github.com/raspberrypi-ui/lxpanel/tree/master/src

void
xfce_panel_plugin_set_taskbar_icon(XfcePanelPlugin *plugin, GtkWidget *image, const char *name)
{
    int size = xfce_panel_plugin_get_size(plugin);
    GtkIconTheme *icon_theme = gtk_icon_theme_get_default();
    GdkPixbuf *pixbuf = xfce_panel_pixbuf_from_source(name, icon_theme, size-2);
    gtk_image_set_from_pixbuf (GTK_IMAGE (image), pixbuf);
    if (pixbuf != NULL) g_object_unref (pixbuf);
    gtk_widget_set_size_request(GTK_WIDGET(plugin), size+4, size);
}

void
xfce_panel_plugin_set_menu_icon(XfcePanelPlugin *plugin, GtkWidget *image, const char *name)
{
    if (strlen(name)==0) {
        gtk_image_clear(GTK_IMAGE (image));
        return;
    }
    gtk_image_set_from_icon_name (GTK_IMAGE (image), name, GTK_ICON_SIZE_MENU);
}

/*
void xfce_panel_plugin_popup_set_position_helper(XfcePanelPlugin *plugin, GtkWidget *attach_to,
                                            GtkWidget *popup, int *x, int *y)
{
    xfce_panel_plugin_position_widget(plugin, popup, attach_to, x, y);
}
*/

static gboolean popup_mapped (GtkWidget *widget, GdkEvent *, gpointer)
{
    gdk_seat_grab (gdk_display_get_default_seat (gdk_display_get_default ()), gtk_widget_get_window (widget), GDK_SEAT_CAPABILITY_ALL_POINTING, TRUE, NULL, NULL, NULL, NULL);
    return FALSE;
}

static gboolean popup_button_press (GtkWidget *widget, GdkEventButton *event, gpointer)
{
    int x, y;
    gtk_window_get_size (GTK_WINDOW (widget), &x, &y);
    if (event->x < 0 || event->y < 0 || event->x > x || event->y > y)
    {
        if (widget) gtk_widget_destroy (widget);
        gdk_seat_ungrab (gdk_display_get_default_seat (gdk_display_get_default ()));
    }
    return FALSE;
}

void xfce_panel_plugin_popup_at_button(XfcePanelPlugin *plugin, GtkWidget *window, GtkWidget *button, gpointer)
{
    gint x, y;
    gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
    gtk_window_set_type_hint (GTK_WINDOW (window), GDK_WINDOW_TYPE_HINT_POPUP_MENU);
    gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window), TRUE);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);
    gtk_widget_show_all (window);
    gtk_widget_hide (window);
    //lxpanel_plugin_popup_set_position_helper (panel, button, window, &x, &y);
    xfce_panel_plugin_position_widget(plugin, window, button, &x, &y);
    gtk_widget_show_all (window);
    gtk_window_present (GTK_WINDOW (window));
    gdk_window_move (gtk_widget_get_window (window), x, y);
    g_signal_connect (G_OBJECT (window), "map-event", G_CALLBACK (popup_mapped), NULL);
    g_signal_connect (G_OBJECT (window), "button-press-event", G_CALLBACK (popup_button_press), NULL);
}


GtkWidget* xfce_panel_plugin_new_menu_item (XfcePanelPlugin *p, const char *text, int maxlen, const char *iconname)
{
    GtkWidget *item = gtk_menu_item_new ();
    gtk_widget_set_name (item, "panelmenuitem");
    GtkWidget *box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, MENU_ICON_SPACE);
    GtkWidget *label = gtk_label_new (text);
    GtkWidget *icon = gtk_image_new ();
    xfce_panel_plugin_set_menu_icon (p, icon, iconname);

    if (maxlen)
    {
        gtk_label_set_max_width_chars (GTK_LABEL (label), maxlen);
        gtk_label_set_ellipsize (GTK_LABEL (label), PANGO_ELLIPSIZE_END);
    }

    gtk_container_add (GTK_CONTAINER (item), box);
    gtk_container_add (GTK_CONTAINER (box), icon);
    gtk_container_add (GTK_CONTAINER (box), label);

    return item;
}

void xfce_panel_plugin_update_menu_icon (GtkWidget *item, GtkWidget *image)
{
    GtkWidget *box = gtk_bin_get_child (GTK_BIN (item));
    GList *children = gtk_container_get_children (GTK_CONTAINER (box));
    GtkWidget *img = (GtkWidget *) children->data;
    gtk_container_remove (GTK_CONTAINER (box), img);
    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 0);
    gtk_box_reorder_child (GTK_BOX (box), image, 0);
}

const char* wrap_get_menu_label(GtkWidget *item)
{
    if (!GTK_IS_BIN (item)) return "";
    GtkWidget *box = gtk_bin_get_child (GTK_BIN (item));
    if (!box) return "";
    GList *children = gtk_container_get_children (GTK_CONTAINER (box));
    if (!children) return "";
    while (children->data)
    {
        if (GTK_IS_LABEL ((GtkWidget *) children->data))
            return gtk_label_get_text (GTK_LABEL ((GtkWidget *) children->data));
        children = children->next;
    }
    return "";
}



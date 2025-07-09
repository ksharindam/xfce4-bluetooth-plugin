#pragma once
#include <gio/gio.h>
#include <libxfce4panel/libxfce4panel.h>

typedef struct {
    GDBusConnection *bus;
    GDBusObjectManager *btobjmanager;//object manager for org.bluez
    GDBusObjectManager *objmanager;// object manager for org.bluez.obex
    GDBusProxy *agentmanager;
    guint agentid;
    GDBusMethodInvocation *invocation;// for returning values of callbacks
    gchar *session;
    gchar *dev_name;//Alias
    gchar *filename;
    gchar *root_path;
    // Transfer settings
    int accept_trusted;
    gchar *incoming_dir;
    // File Transfer settings dialog
    GtkWidget *config_dlg, *filechooser, *accept_trusted_btn;
    // Accept file confirmation dialog
    GtkWidget *confirm_dlg;
    XfcePanelPlugin *plugin;
} Obex;


Obex* obex_create (XfcePanelPlugin *plugin);
void obex_destroy (Obex *obex);

// Show desktop notification
void send_notification (const gchar *title, const gchar *text, const gchar *icon_name);

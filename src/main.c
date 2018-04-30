/*
 * This file is part of budgie-desktop-icons.
 *
 * Copyright © 2018 Budgie Desktop Developers
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <gtk/gtk.h>

#include "desktop-manager.h"
#include "util.h"

#define APP_ID "org.budgie-desktop.icons"

static BudgieDesktopManager *manager = NULL;

static void app_activate(__budgie_unused__ GApplication *app, __budgie_unused__ gpointer v)
{
        if (manager) {
                return;
        }
        manager = budgie_desktop_manager_new();
        g_message("Activated..");
}

static void app_shutdown(__budgie_unused__ GApplication *app, __budgie_unused__ gpointer v)
{
        if (!manager) {
                return;
        }
        g_object_unref(manager);
        manager = NULL;
        g_message("Shutdown");
}

int main(int argc, char **argv)
{
        g_autoptr(GtkApplication) app = NULL;

        app = gtk_application_new(APP_ID, G_APPLICATION_FLAGS_NONE);
        g_application_set_default(G_APPLICATION(app));
        g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
        g_signal_connect(app, "shutdown", G_CALLBACK(app_shutdown), NULL);
        return g_application_run(G_APPLICATION(app), argc, argv);
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */

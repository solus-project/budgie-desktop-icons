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

#define _GNU_SOURCE

#include "util.h"

#include "desktop-manager.h"
#include "desktop-window.h"

#include <gtk/gtk.h>

/**
 * TODO: Provide less shitty CSS.
 */
#define CSS_DATA                                                                                   \
        "\
* { \
        background-color: transparent; \
        background-image: none; \
} \
"

struct _BudgieDesktopManagerClass {
        GObjectClass parent_class;
};

/**
 * BudgieDesktopManager is used to manage the display and appropriately construct
 * windows per output.
 */
struct _BudgieDesktopManager {
        GObject parent;

        GHashTable *windows;
};

G_DEFINE_TYPE(BudgieDesktopManager, budgie_desktop_manager, G_TYPE_OBJECT)

static void budgie_desktop_manager_screens_changed(BudgieDesktopManager *self, GdkScreen *screen);
static void budgie_desktop_manager_init_css(void);

/**
 * budgie_desktop_manager_new:
 *
 * Construct a new BudgieDesktopManager object
 */
BudgieDesktopManager *budgie_desktop_manager_new()
{
        return g_object_new(BUDGIE_TYPE_DESKTOP_MANAGER, NULL);
}

/**
 * budgie_desktop_manager_dispose:
 *
 * Clean up a BudgieDesktopManager instance
 */
static void budgie_desktop_manager_dispose(GObject *obj)
{
        BudgieDesktopManager *self = NULL;
        self = BUDGIE_DESKTOP_MANAGER(obj);

        g_clear_pointer(&self->windows, g_hash_table_unref);

        G_OBJECT_CLASS(budgie_desktop_manager_parent_class)->dispose(obj);
}

/**
 * budgie_desktop_manager_class_init:
 *
 * Handle class initialisation
 */
static void budgie_desktop_manager_class_init(BudgieDesktopManagerClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = budgie_desktop_manager_dispose;
}

/**
 * budgie_desktop_manager_init:
 *
 * Handle construction of the BudgieDesktopManager
 */
static void budgie_desktop_manager_init(BudgieDesktopManager *self)
{
        GdkScreen *screen = NULL;

        self->windows = g_hash_table_new_full(g_direct_hash,
                                              g_direct_equal,
                                              NULL,
                                              (GDestroyNotify)gtk_widget_destroy);

        screen = gdk_screen_get_default();
        g_signal_connect_swapped(screen,
                                 "monitors-changed",
                                 G_CALLBACK(budgie_desktop_manager_screens_changed),
                                 self);

        /* Fix styling */
        budgie_desktop_manager_init_css();

        /* Fire off the initial change event now */
        budgie_desktop_manager_screens_changed(self, screen);
}

/**
 * budgie_desktop_manager_init_css:
 *
 * Bootstrap necessary CSS data
 */
static void budgie_desktop_manager_init_css(void)
{
        GtkCssProvider *provider = NULL;
        GdkScreen *screen = NULL;

        provider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(provider, CSS_DATA, strlen(CSS_DATA), NULL);
        screen = gdk_screen_get_default();
        gtk_style_context_add_provider_for_screen(screen,
                                                  GTK_STYLE_PROVIDER(provider),
                                                  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

/**
 * budgie_desktop_manager_screens_changed:
 *
 * The screens changed, so let's go do something useful with them.
 */
static void budgie_desktop_manager_screens_changed(BudgieDesktopManager *self, GdkScreen *screen)
{
        GdkDisplay *display = NULL;
        GdkMonitor *monitor = NULL;
        GtkWidget *window = NULL;

        /* Clear existing outputs */
        g_hash_table_remove_all(self->windows);

        /* DEMO: Let's just create a single output here */
        display = gdk_screen_get_display(screen);
        monitor = gdk_display_get_primary_monitor(display);
        window = budgie_desktop_window_new(g_application_get_default(), monitor);

        g_hash_table_insert(self->windows, monitor, window);
        gtk_widget_show_all(window);

        g_message("Screens changed");
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

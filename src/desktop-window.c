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

#include "desktop-window.h"

#include <gtk/gtk.h>

struct _BudgieDesktopWindowClass {
        GtkApplicationWindowClass parent_class;
};

/**
 * BudgieDesktopWindow is used to manage the display and appropriately construct
 * windows per output.
 */
struct _BudgieDesktopWindow {
        GtkApplicationWindow parent;
};

G_DEFINE_TYPE(BudgieDesktopWindow, budgie_desktop_window, GTK_TYPE_APPLICATION_WINDOW)

/**
 * budgie_desktop_window_new:
 *
 * Construct a new BudgieDesktopWindow object
 */
GtkWidget *budgie_desktop_window_new()
{
        return g_object_new(BUDGIE_TYPE_DESKTOP_WINDOW, "window-type", GTK_WINDOW_TOPLEVEL, NULL);
}

/**
 * budgie_desktop_window_dispose:
 *
 * Clean up a BudgieDesktopWindow instance
 */
static void budgie_desktop_window_dispose(GObject *obj)
{
        BudgieDesktopWindow *self = NULL;
        self = BUDGIE_DESKTOP_WINDOW(obj);

        G_OBJECT_CLASS(budgie_desktop_window_parent_class)->dispose(obj);
}

/**
 * budgie_desktop_window_class_init:
 *
 * Handle class initialisation
 */
static void budgie_desktop_window_class_init(BudgieDesktopWindowClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = budgie_desktop_window_dispose;
}

/**
 * budgie_desktop_window_init:
 *
 * Handle construction of the BudgieDesktopWindow
 */
static void budgie_desktop_window_init(BudgieDesktopWindow *self)
{
        GtkWindow *window = GTK_WINDOW(self);

        gtk_window_set_decorated(window, FALSE);
        gtk_window_set_skip_pager_hint(window, TRUE);
        gtk_window_set_skip_taskbar_hint(window, TRUE);
        gtk_window_set_type_hint(window, GDK_WINDOW_TYPE_HINT_DESKTOP);
        gtk_window_set_title(window, "Desktop Window");
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

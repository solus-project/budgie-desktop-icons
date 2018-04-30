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

        GdkMonitor *monitor; /** Our output */
};

G_DEFINE_TYPE(BudgieDesktopWindow, budgie_desktop_window, GTK_TYPE_WINDOW)

enum { PROP_MONITOR = 1, N_PROPS };

static GParamSpec *obj_properties[N_PROPS] = {
        NULL,
};

static void budgie_desktop_window_set_property(GObject *object, guint id, const GValue *value,
                                               GParamSpec *spec)
{
        BudgieDesktopWindow *self = BUDGIE_DESKTOP_WINDOW(object);

        switch (id) {
        case PROP_MONITOR:
                self->monitor = g_value_get_pointer(value);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, spec);
                break;
        }
}

static void budgie_desktop_window_get_property(GObject *object, guint id, GValue *value,
                                               GParamSpec *spec)
{
        BudgieDesktopWindow *self = BUDGIE_DESKTOP_WINDOW(object);

        switch (id) {
        case PROP_MONITOR:
                g_value_set_pointer(value, self->monitor);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, spec);
                break;
        }
}

/**
 * budgie_desktop_window_new:
 *
 * Construct a new BudgieDesktopWindow object
 */
GtkWidget *budgie_desktop_window_new(GApplication *app, GdkMonitor *monitor)
{
        return g_object_new(BUDGIE_TYPE_DESKTOP_WINDOW,
                            "application",
                            app,
                            "type",
                            GTK_WINDOW_TOPLEVEL,
                            "monitor",
                            monitor,
                            NULL);
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
        obj_class->set_property = budgie_desktop_window_set_property;
        obj_class->get_property = budgie_desktop_window_get_property;

        obj_properties[PROP_MONITOR] = g_param_spec_pointer("monitor",
                                                            "The GdkMonitor",
                                                            "Corresponding GdkMonitor",
                                                            G_PARAM_CONSTRUCT | G_PARAM_READWRITE);
        g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
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

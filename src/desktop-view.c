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

#include "desktop-view.h"

#include <gtk/gtk.h>

struct _BudgieDesktopViewClass {
        GtkEventBoxClass parent_class;
};

/**
 * BudgieDesktopView is contained with a BudgieDesktopWindow and provides
 * basic management and display of desktop icons.
 */
struct _BudgieDesktopView {
        GtkEventBox parent;
};

G_DEFINE_TYPE(BudgieDesktopView, budgie_desktop_view, GTK_TYPE_EVENT_BOX)

/**
 * budgie_desktop_view_new:
 *
 * Construct a new BudgieDesktopView object
 */
GtkWidget *budgie_desktop_view_new()
{
        return g_object_new(BUDGIE_TYPE_DESKTOP_VIEW, NULL);
}

/**
 * budgie_desktop_view_dispose:
 *
 * Clean up a BudgieDesktopView instance
 */
static void budgie_desktop_view_dispose(GObject *obj)
{
        BudgieDesktopView *self = NULL;
        self = BUDGIE_DESKTOP_VIEW(obj);

        G_OBJECT_CLASS(budgie_desktop_view_parent_class)->dispose(obj);
}

/**
 * budgie_desktop_view_class_init:
 *
 * Handle class initialisation
 */
static void budgie_desktop_view_class_init(BudgieDesktopViewClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = budgie_desktop_view_dispose;
}

/**
 * budgie_desktop_view_init:
 *
 * Handle construction of the BudgieDesktopView
 */
static void budgie_desktop_view_init(BudgieDesktopView *self)
{
        /* Protect against future GTK jankery */
        gtk_event_box_set_visible_window(GTK_EVENT_BOX(self), FALSE);
        gtk_event_box_set_above_child(GTK_EVENT_BOX(self), FALSE);

        /* Force alignment */
        gtk_widget_set_halign(GTK_WIDGET(self), GTK_ALIGN_FILL);
        gtk_widget_set_valign(GTK_WIDGET(self), GTK_ALIGN_FILL);
        gtk_widget_set_hexpand(GTK_WIDGET(self), TRUE);
        gtk_widget_set_vexpand(GTK_WIDGET(self), TRUE);
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

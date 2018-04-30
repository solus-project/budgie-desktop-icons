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

        GtkWidget *icon_view;

        /* Bottom metrics */
        gint icon_height;
        gint icon_spacing;
};

G_DEFINE_TYPE(BudgieDesktopView, budgie_desktop_view, GTK_TYPE_EVENT_BOX)

static void budgie_desktop_view_demo_code(BudgieDesktopView *self);

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
        GtkWidget *box = NULL;

        /* TODO: Make properties */
        self->icon_height = 64;
        self->icon_spacing = 8;

        /* Force alignment */
        gtk_widget_set_halign(GTK_WIDGET(self), GTK_ALIGN_FILL);
        gtk_widget_set_valign(GTK_WIDGET(self), GTK_ALIGN_FILL);
        gtk_widget_set_hexpand(GTK_WIDGET(self), TRUE);
        gtk_widget_set_vexpand(GTK_WIDGET(self), TRUE);

        /* Set up the icon view */
        self->icon_view = gtk_icon_view_new();

        /* Force some initial "sane" sizes */
        gtk_icon_view_set_columns(GTK_ICON_VIEW(self->icon_view), 1);
        gtk_icon_view_set_item_width(GTK_ICON_VIEW(self->icon_view), self->icon_height);
        gtk_icon_view_set_row_spacing(GTK_ICON_VIEW(self->icon_view), self->icon_spacing);
        gtk_icon_view_set_column_spacing(GTK_ICON_VIEW(self->icon_view), self->icon_spacing);

        gtk_icon_view_set_item_orientation(GTK_ICON_VIEW(self->icon_view),
                                           GTK_ORIENTATION_VERTICAL);

        gtk_icon_view_set_text_column(GTK_ICON_VIEW(self->icon_view), 0);
        gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(self->icon_view), 1);
        gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(self->icon_view), GTK_SELECTION_MULTIPLE);

        box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(self), box);
        gtk_box_pack_start(GTK_BOX(box), self->icon_view, TRUE, TRUE, 0);

        /* Go do demo bits */
        budgie_desktop_view_demo_code(self);
}

/**
 * budgie_desktop_view_demo_code:
 *
 * Flesh out some basic demo cruft to get the look & feel right
 */
static void budgie_desktop_view_demo_code(BudgieDesktopView *self)
{
        GtkListStore *model = NULL;
        GtkTreeIter iter = { 0 };
        GtkIconTheme *theme = NULL;
        GdkPixbuf *pixbuf = NULL;

        theme = gtk_icon_theme_get_default();
        model = gtk_list_store_new(2, G_TYPE_STRING, GDK_TYPE_PIXBUF);

        /* Set up Home icon */
        pixbuf = gtk_icon_theme_load_icon(theme,
                                          "folder-home",
                                          self->icon_height,
                                          GTK_ICON_LOOKUP_GENERIC_FALLBACK,
                                          NULL);

        gtk_list_store_append(model, &iter);
        gtk_list_store_set(model, &iter, 0, "Home", 1, pixbuf, -1);

        /* Set up Trash icon */
        pixbuf = gtk_icon_theme_load_icon(theme,
                                          "user-trash",
                                          self->icon_height,
                                          GTK_ICON_LOOKUP_GENERIC_FALLBACK,
                                          NULL);
        gtk_list_store_append(model, &iter);
        gtk_list_store_set(model, &iter, 0, "Trash", 1, pixbuf, -1);

        /* Set the model */
        gtk_icon_view_set_model(GTK_ICON_VIEW(self->icon_view), GTK_TREE_MODEL(model));
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

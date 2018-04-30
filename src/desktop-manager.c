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

#include <gtk/gtk.h>

struct _BudgieDesktopManagerClass {
        GObjectClass parent_class;
};

/**
 * BudgieDesktopManager is used to manage the display and appropriately construct
 * windows per output.
 */
struct _BudgieDesktopManager {
        GObject parent;

        int __reserved1;
};

G_DEFINE_TYPE(BudgieDesktopManager, budgie_desktop_manager, G_TYPE_OBJECT)

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

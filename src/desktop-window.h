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

#pragma once

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _BudgieDesktopWindow BudgieDesktopWindow;
typedef struct _BudgieDesktopWindowClass BudgieDesktopWindowClass;

#define BUDGIE_TYPE_DESKTOP_WINDOW budgie_desktop_window_get_type()
#define BUDGIE_DESKTOP_WINDOW(o)                                                                   \
        (G_TYPE_CHECK_INSTANCE_CAST((o), BUDGIE_TYPE_DESKTOP_WINDOW, BudgieDesktopWindow))
#define BUDGIE_IS_DESKTOP_WINDOW(o) (G_TYPE_CHECK_INSTANCE_TYPE((o), BUDGIE_TYPE_DESKTOP_WINDOW))
#define BUDGIE_DESKTOP_WINDOW_CLASS(o)                                                             \
        (G_TYPE_CHECK_CLASS_CAST((o), BUDGIE_TYPE_DESKTOP_WINDOW, BudgieDesktopWindowClass))
#define BUDGIE_IS_DESKTOP_WINDOW_CLASS(o) (G_TYPE_CHECK_CLASS_TYPE((o), BUDGIE_TYPE_DESKTOP_WINDOW))
#define BUDGIE_DESKTOP_WINDOW_GET_CLASS(o)                                                         \
        (G_TYPE_INSTANCE_GET_CLASS((o), BUDGIE_TYPE_DESKTOP_WINDOW, BudgieDesktopWindowClass))

/**
 * Construct a new BudgieDesktopWindow
 */
GtkWidget *budgie_desktop_window_new(void);

GType budgie_desktop_window_get_type(void);

G_END_DECLS

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

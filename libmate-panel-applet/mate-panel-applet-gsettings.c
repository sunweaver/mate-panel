/*
 * mate-panel-applet-gsettings.c: panel applet preferences handling.
 *
 * Copyright (C) 2012 Stefano Karapetsas
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Authors:
 *     Stefano Karapetsas <stefano@karapetsas.com>
 */

#include <gtk/gtk.h>
#include <gio/gio.h>

#include "mate-panel-applet.h"
#include "mate-panel-applet-gsettings.h"

GSettings *
mate_panel_applet_settings_new (MatePanelApplet *applet, gchar *schema)
{
    GSettings *settings = NULL;
    gchar *path;

    g_return_val_if_fail (PANEL_IS_APPLET (applet), NULL);

    path = mate_panel_applet_get_preferences_path (applet);

    if (path)
        settings = g_settings_new_with_path (schema, path);
        g_free (path);

    return settings;
}

GList*
mate_panel_applet_settings_get_glist (GSettings *settings, gchar *key)
{
    gchar **array;
    GList *list = NULL;
    gint i;
    array = g_settings_get_strv (settings, key);
    if (array != NULL) {
        for (i = 0; array[i]; i++) {
            list = g_list_append (list, g_strdup (array[i]));
        }
    }
    g_strfreev (array);
    return list;
}

void
mate_panel_applet_settings_set_glist (GSettings *settings, gchar *key, GList *list)
{
    gchar **array;
    GList *l;
    gint i;
    for (l = list; l; l = l->next) {
        array[i] = g_strdup (l->data);
        i++;
    }
    array[i] = NULL;
    g_settings_set_strv (settings, key, (const gchar **) array);
    g_strfreev (array);
}

GSList*
mate_panel_applet_settings_get_gslist (GSettings *settings, gchar *key)
{
    gchar **array;
    GSList *list = NULL;
    gint i;
    array = g_settings_get_strv (settings, key);
    if (array != NULL) {
        for (i = 0; array[i]; i++) {
            list = g_slist_append (list, g_strdup (array[i]));
        }
    }
    g_strfreev (array);
    return list;
}

void
mate_panel_applet_settings_set_gslist (GSettings *settings, gchar *key, GSList *list)
{
    gchar **array;
    GSList *l;
    gint i;
    for (l = list; l; l = l->next) {
        array[i] = g_strdup (l->data);
        i++;
    }
    array[i] = NULL;
    g_settings_set_strv (settings, key, (const gchar **) array);
    g_strfreev (array);
}

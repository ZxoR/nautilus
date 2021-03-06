/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */

/* nautilus-global-preferences.c - Nautilus specific preference keys and
                                   functions.

   Copyright (C) 1999, 2000, 2001 Eazel, Inc.

   The Gnome Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The Gnome Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the Gnome Library; see the file COPYING.LIB.  If not,
   see <http://www.gnu.org/licenses/>.

   Authors: Ramiro Estrugo <ramiro@eazel.com>
*/

#include <config.h>
#include "nautilus-global-preferences.h"

#include "nautilus-file-utilities.h"
#include "nautilus-file.h"
#include <eel/eel-glib-extensions.h>
#include <eel/eel-gtk-extensions.h>
#include <eel/eel-stock-dialogs.h>
#include <eel/eel-string.h>
#include <glib/gi18n.h>

GSettings *nautilus_preferences;
GSettings *nautilus_icon_view_preferences;
GSettings *nautilus_list_view_preferences;
GSettings *nautilus_desktop_preferences;
GSettings *nautilus_window_state;
GSettings *gtk_filechooser_preferences;
GSettings *gnome_lockdown_preferences;
GSettings *gnome_background_preferences;
GSettings *gnome_interface_preferences;
GSettings *gnome_privacy_preferences;

/*
 * Public functions
 */
char *
nautilus_global_preferences_get_default_folder_viewer_preference_as_iid (void)
{
	int preference_value;
	const char *viewer_iid;

	preference_value =
		g_settings_get_enum (nautilus_preferences, NAUTILUS_PREFERENCES_DEFAULT_FOLDER_VIEWER);

	if (preference_value == NAUTILUS_DEFAULT_FOLDER_VIEWER_LIST_VIEW) {
		viewer_iid = NAUTILUS_LIST_VIEW_IID;
	} else {
		viewer_iid = NAUTILUS_CANVAS_VIEW_IID;
	}

	return g_strdup (viewer_iid);
}

void
nautilus_global_preferences_init (void)
{
	static gboolean initialized = FALSE;

	if (initialized) {
		return;
	}

	initialized = TRUE;

	nautilus_preferences = g_settings_new("org.gnome.nautilus.preferences");
	nautilus_window_state = g_settings_new("org.gnome.nautilus.window-state");
	nautilus_icon_view_preferences = g_settings_new("org.gnome.nautilus.icon-view");
	nautilus_list_view_preferences = g_settings_new("org.gnome.nautilus.list-view");
	nautilus_desktop_preferences = g_settings_new("org.gnome.nautilus.desktop");
        /* Some settings such as show hidden files are shared between Nautilus and GTK file chooser */
        gtk_filechooser_preferences = g_settings_new_with_path ("org.gtk.Settings.FileChooser",
                                                                "/org/gtk/settings/file-chooser/");
	gnome_lockdown_preferences = g_settings_new("org.gnome.desktop.lockdown");
	gnome_background_preferences = g_settings_new("org.gnome.desktop.background");
	gnome_interface_preferences = g_settings_new ("org.gnome.desktop.interface");
	gnome_privacy_preferences = g_settings_new ("org.gnome.desktop.privacy");
}

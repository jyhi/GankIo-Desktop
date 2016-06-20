/* GankIo-Desktop.c: GankIo-Desktop main program
 * Copyright (C) 2016 Junde Yhi.
 * This file is part of GankIo-Desktop.
 *
 * GankIo-Desktop is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GankIo-Desktop is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GankIo-Desktop.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

GtkWidget * header_bar_create (GtkWidget *searchBar);
void searchEntryMain_stop_search_cb (GtkSearchEntry *entry, GtkWidget *searchBar);
void btnSearch_toggled_cb (GtkToggleButton *btn, GtkWidget *stackContentSearch);

gint main (gint argc, gchar **argv)
{
    GtkWidget *frmMain = NULL;
    GtkWidget *stackContentSearch = NULL;
    GtkBuilder *builder = NULL;

    gtk_init (&argc, &argv);

    builder = gtk_builder_new_from_file ("frmMain.glade");

    // Get object handles
    frmMain = GTK_WIDGET (gtk_builder_get_object (builder, "frmMain"));
    stackContentSearch = GTK_WIDGET (gtk_builder_get_object (builder, "stackContentSearch"));

    // Connect signals.
    // For particular signals, please refer to Glade files.
    gtk_builder_connect_signals (builder, NULL);

    // Add a header bar for frmMain to make it prettier.
    // NOTE: It's impossible to create it in Glade.
    GtkWidget *headerBar = header_bar_create (stackContentSearch);
    gtk_window_set_titlebar (GTK_WINDOW (frmMain), headerBar);

    gtk_widget_show_all (frmMain);
    gtk_main ();

    return 0;
}

GtkWidget * header_bar_create (GtkWidget *stackContentSearch)
{
    GtkWidget *header = gtk_header_bar_new ();
    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header), TRUE);
    gtk_header_bar_set_title (GTK_HEADER_BAR (header), "Gank.io Desktop");
    gtk_header_bar_set_has_subtitle (GTK_HEADER_BAR (header), FALSE);

    // Search button on the right
    GtkWidget *btn = gtk_toggle_button_new ();
    GIcon *icon = g_themed_icon_new ("search-symbolic");
    GtkWidget *image = gtk_image_new_from_gicon (icon, GTK_ICON_SIZE_BUTTON);
    g_object_unref (icon);
    gtk_container_add (GTK_CONTAINER (btn), image);
    gtk_header_bar_pack_end (GTK_HEADER_BAR (header), btn);

    // Connect the search button's "toggled" signal to the search bar
    g_signal_connect (btn, "toggled", G_CALLBACK (btnSearch_toggled_cb), stackContentSearch);

    return header;
}

void searchEntryMain_stop_search_cb (GtkSearchEntry *entry, GtkWidget *searchBar)
{
    // Clear search entry, stay standby.
    gtk_search_bar_set_search_mode (GTK_SEARCH_BAR (searchBar), TRUE);

    return;
}

void btnSearch_toggled_cb (GtkToggleButton *btn, GtkWidget *stackContentSearch)
{
    GtkWidget *child = NULL;

    // NOTE: Signal binding callback functions cannot pass multiple arguments simultaneously.
    //       We need to get the child of the stack first, and then perform switch.
    //       See Glade file for particular child name.
    if (gtk_toggle_button_get_active (btn)) {
        child = gtk_stack_get_child_by_name (GTK_STACK (stackContentSearch), "Search");
    } else {
        child = gtk_stack_get_child_by_name (GTK_STACK (stackContentSearch), "Content");
    }

    if (child) {
        gtk_stack_set_visible_child (GTK_STACK (stackContentSearch), child);
    } else {
        g_warning ("Cannot switch between content and search: child not found");
    }

    return;
}

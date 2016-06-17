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

GtkWidget * header_bar_create ();
gboolean frmMain_key_press_event_cb (GtkWidget *widget, GdkEvent *event, GtkWidget *searchBar);
void searchEntryMain_stop_search_cb (GtkSearchEntry *entry, GtkWidget *searchBar);

gint main (gint argc, gchar **argv)
{
    GtkWidget *frmMain;
    GtkBuilder *builder;

    gtk_init (&argc, &argv);

    builder = gtk_builder_new_from_file ("frmMain.glade");

    // Get object handles
    frmMain = GTK_WIDGET (gtk_builder_get_object (builder, "frmMain"));\

    // Connect signals.
    // For particular signals, please refer to Glade files.
    gtk_builder_connect_signals (builder, NULL);

    // Add a header bar for frmMain to make it prettier.
    // NOTE: It's impossible to create it in Glade.
    GtkWidget *headerBar = header_bar_create ();
    gtk_window_set_titlebar (GTK_WINDOW (frmMain), headerBar);

    gtk_widget_show_all (frmMain);
    gtk_main ();

    return 0;
}

GtkWidget * header_bar_create ()
{
    GtkWidget *header = gtk_header_bar_new ();
    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header), TRUE);
    gtk_header_bar_set_title (GTK_HEADER_BAR (header), "Gank.io Desktop");
    gtk_header_bar_set_has_subtitle (GTK_HEADER_BAR (header), FALSE);

    // Search button on the right
    GtkWidget *btn = gtk_button_new ();
    GIcon *icon = g_themed_icon_new ("search-symbolic");
    GtkWidget *image = gtk_image_new_from_gicon (icon, GTK_ICON_SIZE_BUTTON);
    g_object_unref (icon);
    gtk_container_add (GTK_CONTAINER (btn), image);
    gtk_header_bar_pack_end (GTK_HEADER_BAR (header), btn);

    // Search bar integration
    // GtkWidget *searchBar = gtk_search_bar_new ();
    // gtk_box_pack_start (GTK_BOX (box), searchBar, FALSE, FALSE, 0);
    // GtkWidget *searchEntry = gtk_search_entry_new ();
    // gtk_container_add (GTK_CONTAINER (searchBar), searchEntry);

    // Connect the search button's XXX to the search entry

    return header;
}

gboolean frmMain_key_press_event_cb (GtkWidget *widget, GdkEvent *event, GtkWidget *searchBar)
{
    // Search bar on the top is by default hidden. Show it if it's hiding.
    if (!gtk_widget_is_visible (searchBar)) {
        gtk_widget_show (searchBar);
    } else {}

    return gtk_search_bar_handle_event (GTK_SEARCH_BAR (searchBar), event);
}

void searchEntryMain_stop_search_cb (GtkSearchEntry *entry, GtkWidget *searchBar)
{
    // After searching, hide the search bar.
    if (gtk_widget_is_visible (searchBar)) {
        gtk_widget_hide (searchBar);
    } else {}
}

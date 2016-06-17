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
void btnSearch_clicked_cb (GtkButton *btn, GtkWidget *searchBar);
void searchBarMain_show_cb (GtkWidget *searchBar, GtkWidget *stackContectSearch);
void searchBarMain_hide_cb (GtkWidget *searchBar, GtkWidget *stackContectSearch);

gint main (gint argc, gchar **argv)
{
    GtkWidget *frmMain;
    GtkWidget *searchBarMain;
    GtkBuilder *builder;

    gtk_init (&argc, &argv);

    builder = gtk_builder_new_from_file ("frmMain.glade");

    // Get object handles
    frmMain = GTK_WIDGET (gtk_builder_get_object (builder, "frmMain"));
    searchBarMain = GTK_WIDGET (gtk_builder_get_object (builder, "searchBarMain"));

    // Connect signals.
    // For particular signals, please refer to Glade files.
    gtk_builder_connect_signals (builder, NULL);

    // Add a header bar for frmMain to make it prettier.
    // NOTE: It's impossible to create it in Glade.
    GtkWidget *headerBar = header_bar_create (searchBarMain);
    gtk_window_set_titlebar (GTK_WINDOW (frmMain), headerBar);

    gtk_widget_show_all (frmMain);
    gtk_main ();

    return 0;
}

GtkWidget * header_bar_create (GtkWidget *searchBar)
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

    // Connect the search button's "clicked" signal to the search bar
    g_signal_connect (btn, "clicked", G_CALLBACK (btnSearch_clicked_cb), searchBar);

    return header;
}

void searchEntryMain_stop_search_cb (GtkSearchEntry *entry, GtkWidget *searchBar)
{
    // After searching, hide the search bar.
    if (gtk_widget_is_visible (searchBar)) {
        gtk_widget_hide (searchBar);
    } else {}

    return;
}

void btnSearch_clicked_cb (GtkButton *btn, GtkWidget *searchBar)
{
    // Show search bar and be ready to show search results.
    if (!gtk_widget_is_visible (searchBar)) {
        gtk_widget_show (searchBar);
        gtk_search_bar_set_search_mode (GTK_SEARCH_BAR (searchBar), TRUE);
    } else {
        gtk_widget_hide (searchBar);
    }

    return;
}

void searchBarMain_show_cb (GtkWidget *searchBar, GtkWidget *stackContectSearch)
{
    // When the search bar shows up, the search result screen should shows.
    // NOTE: Signal binding callback functions cannot pass multiple arguments simultaneously.
    //       We need to get the child of the stack first, and then perform switch.
    //       See Glade file for particular child name.
    GtkWidget *child = gtk_stack_get_child_by_name (GTK_STACK (stackContectSearch), "SearchResultsTips");
    if (child) {
        gtk_stack_set_visible_child (GTK_STACK (stackContectSearch), child);
    } else {
        g_warning ("child not found");
    }

    return;
}

void searchBarMain_hide_cb (GtkWidget *searchBar, GtkWidget *stackContectSearch)
{
    // When the search bar hides, the content screen should shows.
    // NOTE: Get another child first. See searchBarMain_show_cb.
    GtkWidget *child = gtk_stack_get_child_by_name (GTK_STACK (stackContectSearch), "Content");
    gtk_stack_set_visible_child (GTK_STACK (stackContectSearch), child);

    return;
}

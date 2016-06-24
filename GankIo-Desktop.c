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
void btnSearch_toggled_cb (GtkToggleButton *btn, GtkWidget *stackShowSearch);
void btnContentBack_clicked_cb (GtkButton *btn, GtkWidget *stackInfoContent);
void btnContentSettings_clicked_cb (GtkButton *btn, GtkWidget *popoverMenuContentSettings);

void btnsInfoTitle_clicked_cb (GtkButton *btn, GtkWidget *comboBoxTextSortedDataType);
void comboBoxTextSortedDataType_changed_cb (GtkComboBox *comboBox, GtkWidget *stackDailySorted);

void btnPicToday_clicked_cb (GtkButton *btn, GtkWidget *stackInfoContent);

gint main (gint argc, gchar **argv)
{
    GtkWidget *frmMain = NULL;
    GtkWidget *stackShowSearch = NULL;
    GtkBuilder *builder = NULL;

    gtk_init (&argc, &argv);

    builder = gtk_builder_new_from_file ("frmMain.glade");

    // Get object handles
    frmMain = GTK_WIDGET (gtk_builder_get_object (builder, "frmMain"));
    stackShowSearch = GTK_WIDGET (gtk_builder_get_object (builder, "stackShowSearch"));

    // Connect signals.
    // For particular signals, please refer to Glade files.
    gtk_builder_connect_signals (builder, NULL);

    // Add a header bar for frmMain to make it prettier.
    // NOTE: It's impossible to create it in Glade.
    GtkWidget *headerBar = header_bar_create (stackShowSearch);
    gtk_window_set_titlebar (GTK_WINDOW (frmMain), headerBar);

    gtk_widget_show_all (frmMain);
    gtk_main ();

    return 0;
}

GtkWidget * header_bar_create (GtkWidget *stackShowSearch)
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
    g_signal_connect (btn, "toggled", G_CALLBACK (btnSearch_toggled_cb), stackShowSearch);

    return header;
}

void searchEntryMain_stop_search_cb (GtkSearchEntry *entry, GtkWidget *searchBar)
{
    // Clear search entry, stay standby.
    gtk_search_bar_set_search_mode (GTK_SEARCH_BAR (searchBar), TRUE);

    return;
}

void btnSearch_toggled_cb (GtkToggleButton *btn, GtkWidget *stackShowSearch)
{
    GtkWidget *child = NULL;

    // NOTE: Signal binding callback functions cannot pass multiple arguments simultaneously.
    //       We need to get the child of the stack first, and then perform switch.
    //       See Glade file for particular child name.
    if (gtk_toggle_button_get_active (btn)) {
        child = gtk_stack_get_child_by_name (GTK_STACK (stackShowSearch), "Search");
    } else {
        child = gtk_stack_get_child_by_name (GTK_STACK (stackShowSearch), "Content");
    }

    if (child) {
        gtk_stack_set_visible_child (GTK_STACK (stackShowSearch), child);
    } else {
        g_warning ("Cannot switch between show and search: child not found");
    }

    return;
}

void btnContentBack_clicked_cb (GtkButton *btn, GtkWidget *stackInfoContent)
{
    GtkWidget *prev = gtk_stack_get_child_by_name (GTK_STACK (stackInfoContent), "Info");
    if (prev) {
        gtk_stack_set_visible_child (GTK_STACK (stackInfoContent), prev);
    } else {
        g_warning ("Cannot switch between info and content: child not found");
    }

    return;
}

void btnContentSettings_clicked_cb (GtkButton *btn, GtkWidget *popoverMenuContentSettings)
{
    // Show popup menu.
    gtk_widget_set_visible (popoverMenuContentSettings, !gtk_widget_is_visible (popoverMenuContentSettings));
    return;
}

void btnsInfoTitle_clicked_cb (GtkButton *btn, GtkWidget *comboBoxTextSortedDataType)
{
    // Unified interface for title buttons in page "Today".
    // Determine which button is clicked, switch the stack, and change the combo box.

    // NOTE: We just cannot switch the stack here by calling gtk_builder_get_object again:
    //   - GtkBuilder doesn't manage constructed widgets; multiple calls to btnsInfoTitle_clicked_cb
    //       will cause memory leak.
    //   - When we construct a new GtkBuilder, a new instance is created. Thus, operations towards
    //       this new GtkBuilder will make no sense on the current window.
    //
    // The switching function is now handled by the combo box itself (when content is changed).
    //   See comboBoxTextSortedDataType_changed_cb

    // Change the combo box to the resource type which we need to look for
    // NOTE: 'btn' is the button clicked by user.
    // NOTE: These 6 buttons are named in Glade. See the .glade file for details.
    const gchar *nameOfWidget = gtk_widget_get_name (GTK_WIDGET (btn));
    if (g_strcmp0 (nameOfWidget, "btnPicTodayTitle") == 0) {
        // Meizi (Today)
        gtk_combo_box_set_active (GTK_COMBO_BOX (comboBoxTextSortedDataType), 0);
    } else if (g_strcmp0 (nameOfWidget, "btnMovTodayTitle") == 0) {
        // Relaxing Movie(s) (Today)
        gtk_combo_box_set_active (GTK_COMBO_BOX (comboBoxTextSortedDataType), 1);
    } else if (g_strcmp0 (nameOfWidget, "btnAndroidTitle") == 0) {
        // Android
        gtk_combo_box_set_active (GTK_COMBO_BOX (comboBoxTextSortedDataType), 2);
    } else if (g_strcmp0 (nameOfWidget, "btnIosTitle") == 0) {
        // iOS
        gtk_combo_box_set_active (GTK_COMBO_BOX (comboBoxTextSortedDataType), 3);
    } else if (g_strcmp0 (nameOfWidget, "btnFrontEndTitle") == 0) {
        // Front-end
        gtk_combo_box_set_active (GTK_COMBO_BOX (comboBoxTextSortedDataType), 4);
    } else if (g_strcmp0 (nameOfWidget, "btnExtendResTitle") == 0) {
        // Extend Resources
        gtk_combo_box_set_active (GTK_COMBO_BOX (comboBoxTextSortedDataType), 5);
    } else {
        // Something happened.
        g_warning ("%s: %s: %d: cannot get proper caller's widget name.", __FILE__, __func__, __LINE__);
    }

    return;
}

void comboBoxTextSortedDataType_changed_cb (GtkComboBox *comboBox, GtkWidget *stackDailySorted)
{
    // Work around for btnsInfoTitle_clicked_cb's not switching the stack.
    // When the text in combo box changed, switch the stackDailySorted to the sorted data page.
    gtk_stack_set_visible_child_name (GTK_STACK (stackDailySorted), "Sorted Data");
    return;
}

void btnPicToday_clicked_cb (GtkButton *btn, GtkWidget *stackInfoContent)
{
    gtk_stack_set_visible_child_name (GTK_STACK (stackInfoContent), "Content");
    return;
}

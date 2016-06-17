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

gint main (gint argc, gchar **argv)
{
    guint retVal;
    GtkWidget *frmMain;
    GtkBuilder *builder;

    gtk_init (&argc, &argv);

    builder = gtk_builder_new_from_file ("frmMain.glade");

        // Connect signals.
        // For particular signals, please refer to Glade files.
        gtk_builder_connect_signals (builder, NULL);

        // Add a header bar for frmMain to make it prettier.
        // NOTE: It's impossible to create it in Glade.
        GtkWidget *headerBar = header_bar_create ();
        gtk_window_set_titlebar (GTK_WINDOW (frmMain), headerBar);

        gtk_widget_show_all (frmMain);
        gtk_main ();
    }

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

    return header;
}

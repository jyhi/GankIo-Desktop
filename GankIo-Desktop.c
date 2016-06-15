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

int main (int argc, char **argv)
{
    guint retVal;
    GtkWidget *frmMain;
    GtkBuilder *builder;

    gtk_init (&argc, &argv);

    // Keep compability of GTK+ <= 3.10
    //   https://developer.gnome.org/gtk3/stable/GtkBuilder.html#gtk-builder-add-from-file
    builder = gtk_builder_new ();
    retVal  = gtk_builder_add_from_file (builder, "frmMain.glade", NULL);
    if (retVal != 0) {
        frmMain = GTK_WIDGET (gtk_builder_get_object (builder, "frmMain"));

        gtk_widget_show_all (frmMain);
        gtk_main ();
    }

    return 0;
}

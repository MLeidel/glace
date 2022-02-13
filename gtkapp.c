// program

//#include <myc.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <unistd.h>

// Create global vars for gtk widgets

GtkWidget *g_obj_window1;
GtkWidget *g_obj_label1;
GtkWidget *g_obj_entry1;


//Signal Handler Functions 

void on_window1_destroy() {
    gtk_main_quit();
}
void on_entry1_activate() {

}
void on_button1_clicked() {

}
///////////////////////////////////////////////

int main(int argc, char *argv[]) {
    GtkBuilder      *builder;
    GtkWidget       *window1;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    //builder = gtk_builder_new_from_string (glade_xml, -1);
    gtk_builder_add_from_file (builder, "gtkapp.glade", NULL);

    window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    gtk_builder_connect_signals(builder, NULL);

    // set GtkWidget Pointers to their builder objects
    // g_ = GTK_WIDGET(gtk_builder_get_object(builder, "WIDGET_ID"));
    // g_ = GTK_WIDGET(gtk_builder_get_object(builder, "WIDGET_ID"));

    g_obj_window1 = window1;
    g_obj_label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    g_obj_entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    g_object_unref(builder);

    gtk_widget_show(window1);
    gtk_main();

    return 0;
}



char *glade_xml = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!-- Generated with glade 3.22.2 -->\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"3.20\"/>\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <property name=\"title\" translatable=\"yes\">Saving Glace</property>\n\
    <property name=\"default_width\">440</property>\n\
    <property name=\"default_height\">250</property>\n\
    <signal name=\"destroy\" handler=\"on_window1_destroy\" swapped=\"no\"/>\n\
    <child type=\"titlebar\">\n\
      <placeholder/>\n\
    </child>\n\
    <child>\n\
      <object class=\"GtkBox\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <child>\n\
          <object class=\"GtkLabel\" id=\"label1\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"label\" translatable=\"yes\">Label for csketch dev</property>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkEntry\" id=\"entry1\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">True</property>\n\
            <property name=\"text\" translatable=\"yes\">Enter stuff in here ................</property>\n\
            <signal name=\"activate\" handler=\"on_entry1_activate\" swapped=\"no\"/>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">1</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkButton\" id=\"button1\">\n\
            <property name=\"label\">gtk-ok</property>\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">True</property>\n\
            <property name=\"receives_default\">True</property>\n\
            <property name=\"use_stock\">True</property>\n\
            <signal name=\"clicked\" handler=\"on_button1_clicked\" swapped=\"no\"/>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">2</property>\n\
          </packing>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
\0";
// builder = gtk_builder_new_from_string (glade_xml, -1);


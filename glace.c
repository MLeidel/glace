/***
* glace.c
* generates c source code for a gtk GUI from a Glade xml file.
* The GtkWindow id must be "window1" and "destroy" signal set.
* A string of the xml can be optionally included by setting the
* second argument to "xml". First argument is the Glade file name.
***/
#include <myc.h>

#define MAX_OBJ 100
#define MAX_LEN 64
void xml2string();

char gladefile[128] = {'\0'};
bool bxml = false;

FILE *infile;
char inbuf[MAX_L] = {'\0'};

typedef struct wobjs  {
    char class[MAX_LEN];
    char id[MAX_LEN];
} wobjs;

wobjs objs[MAX_OBJ];
int objs_inx = 0;

char sig[MAX_OBJ][MAX_LEN] = {'\0', '\0'};
int sig_inx = 0;

int inx = 0;


/*
                      _
      _ __ ___   __ _(_)_ __
     | '_ ` _ \ / _` | | '_ \
     | | | | | | (_| | | | | |
     |_| |_| |_|\__,_|_|_| |_|

 */


int main (int argc, char *argv[]) {

    if (argc < 2) {
       printf("use:\n./glace gladefile [xml]\n");
       exit(EXIT_FAILURE);
    } else {
        strcpy(gladefile, argv[1]);
    }
    if ( (argc == 3) && (equals(argv[2], "xml")) ) {
        bxml = true;
    }


    char code1[] = "\
// program\n\
\n\
//#include <myc.h>\n\
#include <gtk/gtk.h>\n\
#include <gdk/gdk.h>\n\
#include <unistd.h>\n\
\n\
// Create global vars for gtk widgets\n\
";

    char code2[] = "\
///////////////////////////////////////////////\n\n\
int main(int argc, char *argv[]) {\n\
    GtkBuilder      *builder;\n\
    GtkWidget       *window1;\n\
\n\
    gtk_init(&argc, &argv);\n\
\n\
    builder = gtk_builder_new();\n\
    //builder = gtk_builder_new_from_string (glade_xml, -1);\n\
    gtk_builder_add_from_file (builder, \"XXXXXX\", NULL);\n\
\n\
    window1 = GTK_WIDGET(gtk_builder_get_object(builder, \"window1\"));\n\
    gtk_builder_connect_signals(builder, NULL);\n\
\n\
    // set GtkWidget Pointers to their builder objects\n\
    // g_ = GTK_WIDGET(gtk_builder_get_object(builder, \"WIDGET_ID\"));\n\
    // g_ = GTK_WIDGET(gtk_builder_get_object(builder, \"WIDGET_ID\"));\n\
";

    char code4[] = "\
    g_object_unref(builder);\n\
\n\
    gtk_widget_show(window1);\n\
    gtk_main();\n\
\n\
    return 0;\n\
}\n\
";

    if (file_exists(gladefile)) {
        infile = open_for_read(gladefile);
    } else {
        fprintf(stderr, "\nglade file missing ?\n");
        exit(EXIT_FAILURE);
    }

    while (true) {
        fgets(inbuf, MAX_L, infile);
        if (feof(infile)) break;

        if (contains(inbuf, " id=")) {
            field(objs[objs_inx].class, inbuf, '\"', 1, true);
            field(objs[objs_inx++].id, inbuf, '\"', 3, true);
        }
        if (contains(inbuf, " handler=")) {
            field(sig[sig_inx++], inbuf, '\"', 3, true);
        }
    }

    fclose(infile);

    /*
    OUTPUT BEGINS HERE
    */

    puts(code1);

    // Widget Globals
    for(inx=0; inx < objs_inx; inx++) {
        if (!contains(objs[inx].class, "GtkButton")) {
            printf("GtkWidget *g_obj_%s;\n", objs[inx].id);
        }
    }

    puts("\n\n//Signal Handler Functions \n");

    // Handler function bodies
    for(inx=0; inx < sig_inx; inx++) {
        if (equals(sig[inx], "on_window1_destroy")) {
            printf("void %s() {\n    gtk_main_quit();\n}\n", sig[inx]);
        } else {
            printf("void %s() {\n\n}\n", sig[inx]);
        }
    }

    replace(code2, code2, "XXXXXX", gladefile, 0, 1);
    puts(code2);

    // Print the global type assertions
    for(inx=0; inx < objs_inx; inx++) {
        if (!contains(objs[inx].class, "GtkButton")) {
            if (contains(objs[inx].class, "GtkWindow")) {
                puts("    g_obj_window1 = window1;");
            } else {
                printf("    g_obj_%s = GTK_WIDGET(gtk_builder_get_object(builder, \"%s\"));\n",
                        objs[inx].id,  objs[inx].id);
            }
        }
    }

    puts(code4);

    if (bxml)
        xml2string();

    return 0;
}

/*
    optionally output the glade xml in c string format
    for inclusion at compile time
*/
void xml2string() {
    char line[4096];

    FILE *fh = open_for_read(gladefile);

    puts("\n\nchar *glade_xml = \"\\");

    while(true) {
        fgets(line, 1024, fh);
        if (feof(fh)) break;
        trim(line);
        replace(line, line, "\"", "\\\"", 0, 0);
        strcat(line, "\\n\\");
        printf("%s\n", line);
    }
    fclose(fh);
    puts("\\0\";");
    puts("// builder = gtk_builder_new_from_string (glade_xml, -1);\n");
}

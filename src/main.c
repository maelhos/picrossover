#include "stdinc.h"
#include "picross_field.h"
static int counter = 0;
  
void greet(GtkWidget* widget, gpointer data){
    // printf equivalent in GTK+
    g_print("Welcome to GTK\n");
    g_print("%s clicked %d times\n",
            (char*)data, ++counter);
}
  
void destroy(GtkWidget* widget, gpointer data){
    gtk_main_quit();
}


int main(int argc, char* argv[]){
    FILE* f = fopen("assets/test.asset","rb");


    picross_field PF;
    picross_field_init(&PF);
    picross_field_load(&PF, f);
    
    picross_field_print_ascii(&PF);
    return 0;
}
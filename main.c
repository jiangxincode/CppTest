#include <stdlib.h>
#include "frame.h"
#include "elevator.h"

gint seq[13];

int main(int argc, char *argv[])
{
        info *elev = (info *)malloc(sizeof(info));
        init(elev);

        GtkWidget *window;
        GtkWidget *grid;

        GtkWidget *button_out1_up, *button_out2_up, *button_out3_up, *button_out4_up;
        GtkWidget *button_out2_down, *button_out3_down, *button_out4_down, *button_out5_down;

        GtkWidget *state_in_floor, *state_out_floor, *state_in_directory, *state_out_directory;

        GtkWidget *button_in1, *button_in2, *button_in3, *button_in4, *button_in5;

        GtkWidget *button_close, *button_open;
        GtkWidget *open;

        gtk_init(&argc, &argv);

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
        gtk_window_set_default_size(GTK_WINDOW(window),300,350);
        gtk_window_set_title(GTK_WINDOW(window), "Elevator");

        grid = gtk_grid_new();
        gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
        gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

        button_out1_up = gtk_button_new_with_label("Up");
        button_out2_up = gtk_button_new_with_label("Up");
        button_out3_up = gtk_button_new_with_label("Up");
        button_out4_up = gtk_button_new_with_label("Up");

        button_out2_down = gtk_button_new_with_label("Down");
        button_out3_down = gtk_button_new_with_label("Down");
        button_out4_down = gtk_button_new_with_label("Down");
        button_out5_down = gtk_button_new_with_label("Down");

        /**set the current floor from outdoors*/
        gchar current[32] = {'\0'};
        sprintf(current, "%d", elev->current);
        state_out_floor = gtk_label_new(current);

        /**set the run state from outdoors*/
        gchar *state;
        switch(elev->state)
        {
                case 0: state = "-";break;
                case 1: state = "Up";break;
                case 2: state = "Down";break;
                default: perror("Invalid Run State");break;
        }
        state_out_directory = gtk_label_new(state);

        gtk_grid_attach(GTK_GRID(grid), button_out5_down, 2, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), button_out4_down, 1, 2, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), button_out3_down, 1, 3, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), button_out2_down, 1, 4, 1, 1);

        gtk_grid_attach(GTK_GRID(grid), button_out1_up, 2, 5, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), button_out2_up, 3, 4, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), button_out3_up, 3, 3, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), button_out4_up, 3, 2, 1, 1);

        gtk_grid_attach(GTK_GRID(grid),state_out_floor, 1, 6, 1,1);
        gtk_grid_attach(GTK_GRID(grid), state_out_directory, 3,6,1,1);


        button_in1 = gtk_button_new_with_label("1");
        button_in2 = gtk_button_new_with_label("2");
        button_in3 = gtk_button_new_with_label("3");
        button_in4 = gtk_button_new_with_label("4");
        button_in5 = gtk_button_new_with_label("5");

        state_in_floor = gtk_label_new(current);
        state_in_directory = gtk_label_new(state);

        button_open = gtk_button_new_with_label("Open");
        button_close = gtk_button_new_with_label("Close");
        gchar *is_open;
        switch(elev->door)
        {
                case TRUE: is_open = "Open";break;
                case FALSE: is_open = "Closed";break;
                default :perror("Invalid door state");break;
        }
        open = gtk_label_new(is_open);

        gtk_grid_attach(GTK_GRID(grid), button_in5, 6, 1, 3, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), button_in4, button_in5, GTK_POS_BOTTOM, 3, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), button_in3, button_in4, GTK_POS_BOTTOM, 3, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), button_in2, button_in3, GTK_POS_BOTTOM, 3, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), button_in1, button_in2, GTK_POS_BOTTOM, 3, 1);

        gtk_grid_attach(GTK_GRID(grid), state_in_floor, 6, 6, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), state_in_directory, 8, 6, 1, 1);

        gtk_grid_attach(GTK_GRID(grid), button_open, 6, 7, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), open, 7, 7, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), button_close, 8, 7, 1, 1);


        gtk_container_add(GTK_CONTAINER(window), grid);


        g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

        g_signal_connect(G_OBJECT(button_out1_up), "clicked", G_CALLBACK(click_directory),seq);
        g_signal_connect(G_OBJECT(button_out2_up), "clicked", G_CALLBACK(click_directory),seq+1);
        g_signal_connect(G_OBJECT(button_out2_down), "clicked", G_CALLBACK(click_directory),seq+2);
        g_signal_connect(G_OBJECT(button_out3_up), "clicked", G_CALLBACK(click_directory),seq+3);
        g_signal_connect(G_OBJECT(button_out3_down), "clicked", G_CALLBACK(click_directory),seq+4);
        g_signal_connect(G_OBJECT(button_out4_up), "clicked", G_CALLBACK(click_directory),seq+5);
        g_signal_connect(G_OBJECT(button_out4_down), "clicked", G_CALLBACK(click_directory),seq+6);
        g_signal_connect(G_OBJECT(button_out5_down), "clicked", G_CALLBACK(click_directory),seq+7);

        g_signal_connect(G_OBJECT(button_in1), "clicked", G_CALLBACK(click_directory),seq+8);
        g_signal_connect(G_OBJECT(button_in2), "clicked", G_CALLBACK(click_directory),seq+9);
        g_signal_connect(G_OBJECT(button_in3), "clicked", G_CALLBACK(click_directory),seq+10);
        g_signal_connect(G_OBJECT(button_in4), "clicked", G_CALLBACK(click_directory),seq+11);
        g_signal_connect(G_OBJECT(button_in5), "clicked", G_CALLBACK(click_directory),seq+12);

        g_signal_connect(G_OBJECT(button_open), "clicked", G_CALLBACK(open_door),open);
        g_signal_connect(G_OBJECT(button_close), "clicked", G_CALLBACK(close_door),open);
        gtk_widget_show_all(window);

        gtk_main();

        return 0;
}

//thread.c
/**
在GTK+中应用线程， 要用到gdk_thread_init来在X WINDOW中初始化线程应用，
另外在线程中要对GTK+控件进行操作时还要在操作前执行函数gdk_thread_enter来进入，
操作完成后执行函 数gdk_thread_leave来离开，
在执行GTK+主循环时也是如此，GTK+以此来达到线程安全；
下面代码利用线程创建了一个在屏幕上沿顺时针 运动的图像（24x24像素）：
*/
#include <gtk/gtk.h>

struct _Ourarg
{
        GtkWidget *fixed;
        GtkWidget *image;
        gint right;
        gint left;
};

typedef struct _Ourarg Ourarg;

void image_go(Ourarg *arg)
{
        gint x, y, toward;
        x = y = arg->left;
        toward = 1;
        for(;;)
        {
                g_usleep(1500);
                gdk_threads_enter();
                gtk_fixed_move(GTK_FIXED(arg->fixed),arg->image, x, y);
                switch(toward)
                {
                case 1:
                        x = x + 10;
                        if( x > arg->right ) toward = 2;
                        break;
                case 2:
                        y = y + 10;
                        if( y > arg->right ) toward = 3;
                        break;
                case 3:
                        x = x - 10;
                        if( x < arg->left ) toward = 4;
                        break;
                case 4:
                        y = y -10;
                        if( y < arg->left ) toward = 1;
                }
                gdk_threads_leave();
        }
}

int	main0008(int argc, char* argv[])
{
        GtkWidget *window;
        GtkWidget *vbox, *viewport, *button;
        GtkWidget *image, *fixed;

        Ourarg *arg;

        gdk_threads_init();

        gtk_init(&argc,&argv);

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

        gtk_window_set_title(GTK_WINDOW(window),"线程测试");

        g_signal_connect(G_OBJECT(window),"delete_event", G_CALLBACK(gtk_main_quit),NULL);

        gtk_container_set_border_width(GTK_CONTAINER(window),2);

        vbox = gtk_vbox_new(FALSE,0);
        gtk_container_add(GTK_CONTAINER(window),vbox);

        fixed = gtk_fixed_new();
        gtk_widget_set_usize(fixed,340,340);

        viewport = gtk_viewport_new(NULL,NULL);
        gtk_box_pack_start(GTK_BOX(vbox),viewport,FALSE,FALSE,5);
        gtk_container_add(GTK_CONTAINER(viewport),fixed);

        image = gtk_image_new_from_file("ss.png");
        gtk_fixed_put(GTK_FIXED(fixed),image,40,40);
        button = gtk_button_new_with_label("退出");
        gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5);

        g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK(gtk_main_quit),NULL);

        gtk_widget_show_all(window);

        arg = g_new(Ourarg,1);
        arg->fixed = fixed;
        arg->image = image;
        arg->left = 40;
        arg->right = 260;

        g_thread_new(NULL,image_go, arg);

        gdk_threads_enter();
        gtk_main();
        gdk_threads_leave();
        return FALSE;
}

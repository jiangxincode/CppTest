/**
使用GTK编写中文软件
GTK/GNOME 系列widgets中, 输入和显示已经是国际化了的. 所以用它们编写中文软件十分容易.
把西文软件改写成中文软件也十分容易.

在gtk_init前设置locale: gtk_set_locale()
接着调用 gtk_rc_add_default_file("rcfilename"), 其中rcfilename中 含有缺省的fontset
如果不用资源文件, 则应对widget设置fontset
把文件 gtkrc.zh 拷贝到当前目录下
在 gtk 的 text 组件中如果设置了font, 则不能正常显示中文.
解决的方法是把font释放(unref), 然后使用 gtk_fontset_load 字体集.
对于其它组件也是如此, 有的组件需要先拷贝一个 GtkStyle, 然后按上述方法解决.
下面的程序在显示中文时未使用中文平台, 输入使用的是Chinput中的XIM协议支持
*/
//file entry.c
#define GTK_ENABLE_BROKEN
#include <gtk/gtk.h>
int main0009 (int argc, char *argv[])
{
        GtkWidget *window;
        GtkWidget *vbox;
        GtkWidget *entry;
        GtkWidget *text;
        GtkWidget *button;

        gtk_set_locale();
        gtk_rc_add_default_file("./gtkrc.zh");

        gtk_init (&argc, &argv); /* create a new window */

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_widget_set_usize( GTK_WIDGET (window), 200, 500);
        gtk_window_set_title(GTK_WINDOW (window), "GTK Entry");
        gtk_signal_connect(GTK_OBJECT (window), "delete_event", (GtkSignalFunc) gtk_exit, NULL);

        vbox = gtk_vbox_new (FALSE, 0);
        gtk_container_add (GTK_CONTAINER (window), vbox);

        entry = gtk_entry_new_with_max_length (60);
        gtk_entry_select_region (GTK_ENTRY (entry), 0, GTK_ENTRY(entry)->text_length);
        gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);

        text = gtk_text_new (NULL, NULL);
        gtk_text_set_editable (GTK_TEXT(text), TRUE);
        gtk_box_pack_start (GTK_BOX (vbox), text, TRUE, TRUE, 0);

        button = gtk_button_new_with_label ("关闭窗口");
        gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
        gtk_signal_connect_object (GTK_OBJECT (button), "clicked", GTK_SIGNAL_FUNC(gtk_exit), GTK_OBJECT (window));
        GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
        gtk_widget_grab_default (button);

        gtk_widget_show_all(window);

        gtk_main();
        return(0);
}


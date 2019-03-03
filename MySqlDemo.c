/**
链接mysql并插入数据的GTK+程序
*/

#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GtkWidget *window1;
static GtkWidget *button1;
static GtkWidget *button2;

static gint num=0;


void on_button1_clicked(void);
void on_button2_clicked(void);

/*按钮1的click事件*/
void on_button1_clicked(void)
{
	gchar tmp[100];
	num++;
	if(num>10)
	{
		num=0;
	}
	g_ascii_dtostr(tmp,100,num);
	gtk_window_set_title(GTK_WINDOW(window1),tmp);
}
/*按钮2的click事件*/
void on_button2_clicked(void)
{
	gtk_window_set_title(GTK_WINDOW(window1),"MySql \346\265\213\350\257\225");
	num=0;
}

//静态成员声明

int main0010(int argc,char *argv[])
{
	GtkWidget *hbox1; //横排
	GtkWidget *vbox1; //竖排
	GtkWidget *vbox2;
	gtk_init(&argc,&argv);
	window1=gtk_window_new(GTK_WINDOW_TOPLEVEL);

//其他控件声明
	button1=gtk_button_new_with_label("quit");
	button2=gtk_button_new_with_label("ok");

//回调函数
	g_signal_connect(GTK_BUTTON(button1),"clicked",G_CALLBACK(on_button1_clicked),NULL);
	g_signal_connect(GTK_BUTTON(button2),"clicked",G_CALLBACK(on_button2_clicked),NULL);

//布局容器声明
	hbox1=gtk_hbox_new(FALSE,0);
	vbox1=gtk_vbox_new(FALSE,0);
	vbox2=gtk_vbox_new(FALSE,0);
	gtk_container_set_border_width(GTK_CONTAINER(hbox1),3);
	gtk_container_add(GTK_CONTAINER(window1), hbox1);
//向容器添加控件
	gtk_box_pack_start(GTK_BOX(hbox1),vbox1,FALSE,FALSE,3);
	gtk_box_pack_start(GTK_BOX(hbox1),vbox2,TRUE,TRUE,3);
	gtk_box_pack_start(GTK_BOX(vbox1),button1,FALSE,FALSE,3);
	gtk_box_pack_start(GTK_BOX(vbox1),button2,FALSE,FALSE,3);
//gtk_widget_show (hbox1);

	g_signal_connect(G_OBJECT(window1),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_title(GTK_WINDOW(window1),"MySql Test");
	gtk_window_set_default_size(GTK_WINDOW(window1),300,200);
	gtk_window_set_position(GTK_WINDOW(window1),GTK_WIN_POS_CENTER);
	gtk_widget_show_all(window1);
	gtk_main();
	return 0;
}

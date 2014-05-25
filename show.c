#include "elevator.h"

int printinfo(char *buf,char *temp)
{
	int i;
	for(i=0;i<BUF_MAX;i++)
	{
		buf[i]=*(temp+i);

	}
	return 0;
}
int main(int argc,char *argv[])
{
	char buf_current[BUF_MAX],buf_destination[BUF_MAX],buf_status[BUF_MAX],buf_door[BUF_MAX];

	printf("The show_process exec successfully!\n");
	info *p_map;
	key_t key;
	int shmid;
	if((key=ftok(".",1))<0)
	{
		perror("ftok error!\n");
		exit(1);
	}
	
	shmid=shmget(key,BUFSZ,0666|IPC_CREAT);
	if(shmid<0)
	{
		perror("shmget error!\n");
		exit(1);
	}	
	
	p_map=(info *)shmat(shmid,NULL,0);	//附加共享内存
	
/*对info进行显示*/
	switch(p_map->current){
		case 1:printinfo(buf_current,"current:one");break;
		case 2:printinfo(buf_current,"current:two");break;
		case 3:printinfo(buf_current,"current:three");break;
		case 4:printinfo(buf_current,"current:four");break;
		case 5:printinfo(buf_current,"current:five");break;
		default:printinfo(buf_current,"ERROR!");break;
	}
	switch(p_map->destination){
		case 0:printinfo(buf_destination,"destination:none");break;
		case 1:printinfo(buf_destination,"destination:one");break;
		case 2:printinfo(buf_destination,"destination:two");break;
		case 3:printinfo(buf_destination,"destination:three");break;
		case 4:printinfo(buf_destination,"destination:four");break;
		case 5:printinfo(buf_destination,"destination:five");break;
		default:printinfo(buf_destination,"ERROR!");break;
	}
	switch(p_map->status){
		case 0:printinfo(buf_status,"status:stop");break;
		case 1:printinfo(buf_status,"status:up");break;
		case 2:printinfo(buf_status,"status:down");break;
		default:printinfo(buf_status,"ERROR!");break;
	}
	switch(p_map->door){
		case 1:printinfo(buf_door,"door:closed");break;
		case 2:printinfo(buf_door,"door:open");break;
		default:printinfo(buf_door,"ERROR!");break;
	}
/*对info进行显示*/


	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *grid0;
	GtkWidget *grid1;
	GtkWidget *grid2;
	GtkWidget *grid3;
	GtkWidget *grid4;
	GtkWidget *grid5;
	GtkWidget *label;
	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;

	gtk_init(&argc,&argv);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Elevator");

	grid=gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window),grid);

	grid0=gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid),grid0,0,0,1,1);
	label=gtk_label_new("inter_control");
	gtk_grid_attach(GTK_GRID(grid0),label,0,0,1,1);
	label1=gtk_label_new(buf_current);
	label2=gtk_label_new(buf_destination);	
	label3=gtk_label_new(buf_status);
	label4=gtk_label_new(buf_door);
	gtk_grid_attach(GTK_GRID(grid0),label1,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid0),label2,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid0),label3,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid0),label4,0,4,1,1);
	
	grid1=gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid),grid1,2,0,1,1);
	label=gtk_label_new("floor_one");
	gtk_grid_attach(GTK_GRID(grid1),label,0,0,1,1);
	label1=gtk_label_new(buf_current);
	label2=gtk_label_new(buf_destination);	
	label3=gtk_label_new(buf_status);
	label4=gtk_label_new(buf_door);
	gtk_grid_attach(GTK_GRID(grid1),label1,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid1),label2,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid1),label3,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid1),label4,0,4,1,1);

	grid2=gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid),grid2,0,2,1,1);
	label=gtk_label_new("floor_two");
	gtk_grid_attach(GTK_GRID(grid2),label,0,0,1,1);
	label1=gtk_label_new(buf_current);
	label2=gtk_label_new(buf_destination);	
	label3=gtk_label_new(buf_status);
	label4=gtk_label_new(buf_door);
	gtk_grid_attach(GTK_GRID(grid2),label1,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid2),label2,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid2),label3,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid2),label4,0,4,1,1);
	
	grid3=gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid),grid3,2,2,1,1);
	label=gtk_label_new("floor_three");
	gtk_grid_attach(GTK_GRID(grid3),label,0,0,1,1);
	label1=gtk_label_new(buf_current);
	label2=gtk_label_new(buf_destination);	
	label3=gtk_label_new(buf_status);
	label4=gtk_label_new(buf_door);
	gtk_grid_attach(GTK_GRID(grid3),label1,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid3),label2,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid3),label3,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid3),label4,0,4,1,1);

	grid4=gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid),grid4,0,4,1,1);
	label=gtk_label_new("floor_four");
	gtk_grid_attach(GTK_GRID(grid4),label,0,0,1,1);
	label1=gtk_label_new(buf_current);
	label2=gtk_label_new(buf_destination);	
	label3=gtk_label_new(buf_status);
	label4=gtk_label_new(buf_door);
	gtk_grid_attach(GTK_GRID(grid4),label1,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid4),label2,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid4),label3,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid4),label4,0,4,1,1);

	grid5=gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid),grid5,2,4,1,1);
	label=gtk_label_new("floor_five");
	gtk_grid_attach(GTK_GRID(grid5),label,0,0,1,1);
	label1=gtk_label_new(buf_current);
	label2=gtk_label_new(buf_destination);	
	label3=gtk_label_new(buf_status);
	label4=gtk_label_new(buf_door);
	gtk_grid_attach(GTK_GRID(grid5),label1,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid5),label2,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid5),label3,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid5),label4,0,4,1,1);

	gtk_widget_show_all(window);
	
	gtk_main();

	return 0;
}

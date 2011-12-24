#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>


static int getImgPrefix(char *prefix)
{
	struct stat b;
	int i, ok = 0;
	char filename[80];
	for(i = 0; i < 10; i++) {
		sprintf(filename, "%s%i.gif", "/usr/share/games/nixie-clock/", i);
		ok = ok || lstat(filename, &b);
	}
	if(!ok)  
		sprintf(prefix, "/usr/share/games/nixie-clock/");
	else {		
		ok = 0;
		for(i = 0; i < 10; i++) {
			sprintf(filename, "%i.gif", i);
			ok = ok || lstat(filename, &b);
		}
		if(!ok) sprintf(prefix, "./");
		else return -1;
	
	}
	return 0;
}

static gboolean time_handler(GtkWidget *digits[])
{
	time_t curtime;
	struct tm *loctime;

	curtime = time(NULL);
	loctime = localtime(&curtime);

	char hrs[3], min[3], sec[3], filename[80];
	char img_prefix[80]; 
	if(getImgPrefix(img_prefix)) {		//getImgPrefix returns non-zero value if it cannot find images
		fprintf(stderr, "Cannot find images in /usr/share/games/nixie-clock and in current dir!\n");
		exit(-1);
	}
	strftime(hrs, 3, "%H", loctime);
	strftime(min, 3, "%M", loctime);
	strftime(sec, 3, "%S", loctime);

	sprintf(filename, "%s%c.gif", img_prefix,  sec[1]);
	gtk_image_set_from_file((GtkImage *)digits[0], filename);

	sprintf(filename, "%s%c.gif", img_prefix,  sec[0]);
	gtk_image_set_from_file((GtkImage *)digits[1], filename);

	sprintf(filename, "%s%c.gif", img_prefix,  min[1]);
	gtk_image_set_from_file((GtkImage *)digits[2], filename);

	sprintf(filename, "%s%c.gif", img_prefix,  min[0]);
	gtk_image_set_from_file((GtkImage *)digits[3], filename);

	sprintf(filename, "%s%c.gif", img_prefix,  hrs[1]);
	gtk_image_set_from_file((GtkImage *)digits[4], filename);

	sprintf(filename, "%s%c.gif", img_prefix,  hrs[0]);
	gtk_image_set_from_file((GtkImage *)digits[5], filename);

	return TRUE;
}



int main( int argc, char *argv[])
{
	GtkWidget *window;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	GtkWidget *hour1 = gtk_image_new_from_file("0.gif");
	GtkWidget *hour2 = gtk_image_new_from_file("1.gif");
	GtkWidget *min1 = gtk_image_new_from_file("2.gif");
	GtkWidget *min2 = gtk_image_new_from_file("3.gif");
	GtkWidget *sec1 = gtk_image_new_from_file("4.gif");
	GtkWidget *sec2 = gtk_image_new_from_file("5.gif");
	GtkWidget *box = gtk_hbox_new(1, 0);
	GtkWidget *digits[6];

	gtk_window_set_title(GTK_WINDOW(window), "Nixie clock");
	gtk_window_set_default_size(GTK_WINDOW(window), 180, 64);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	gtk_container_add(GTK_CONTAINER(window), box);
	gtk_container_add(GTK_CONTAINER(box), hour1);
	gtk_container_add(GTK_CONTAINER(box), hour2);
	gtk_container_add(GTK_CONTAINER(box), min1);
	gtk_container_add(GTK_CONTAINER(box), min2);
	gtk_container_add(GTK_CONTAINER(box), sec1);
	gtk_container_add(GTK_CONTAINER(box), sec2);

	digits[0] = sec2; digits[1] = sec1; 
	digits[2] = min2; digits[3] = min1; 
	digits[4] = hour2; digits[5] = hour1;


	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	time_handler(digits);	
	g_timeout_add(1000, (GSourceFunc) time_handler, digits);

	gtk_widget_show_all(window);	
	gtk_main();

	return 0;
}



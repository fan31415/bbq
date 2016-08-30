#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>
#include "chatWindow.h"
#include "chatRecord.h"
#include "showRecord.h"
/* ŽŽœšÒ»žöÐÂµÄºáÏòºÐ£¬Ëü°üº¬Ò»žöÍŒÏñºÍÒ»žö±êÇ©£¬²¢·µ»ØÕâžöºÐ¡£*/
GtkWidget *xpm_label_box( gchar     *xpm_filename,
                          gchar     *label_text )
{
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;

    /* ÎªÍŒÏñºÍ±êÇ©ŽŽœšºÐ */
    box = gtk_hbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);

    /* ŽŽœšÒ»žöÍŒÏñ */
    image = gtk_image_new_from_file (xpm_filename);

    /* Îª°ŽÅ¥ŽŽœšÒ»žö±êÇ© */
    label = gtk_label_new (label_text);

    /* °ÑÍŒÏñºÍ±êÇ©×é×°µœºÐ×ÓÀï */
    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 3);

    gtk_widget_show (image);
    gtk_widget_show (label);

    return box;
}

/* ŽŽœšÒ»žöÐÂµÄ×ÝÏòºÐ×Ó£¬Ëü°üº¬Ò»žö±êÇ©ºÍÒ»žöÍŒÏñ£¬²¢·µ»ØÕâžöºÐ¡£*/
GtkWidget *label_xmp_box( gchar *label_text ,gchar *xpm_filename)
{
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;

    /* ÎªÍŒÏñºÍ±êÇ©ŽŽœšºÐ */
    box = gtk_vbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);

    /* ŽŽœšÒ»žöÍŒÏñ */
    image = gtk_image_new_from_file (xpm_filename);

    /* Îª°ŽÅ¥ŽŽœšÒ»žö±êÇ© */
    label = gtk_label_new (label_text);

    /* °Ñ±êÇ©ºÍÍŒÏñ×é×°µœºÐ×ÓÀï */
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
  
    gtk_widget_show (image);
    gtk_widget_show (label);

    return box;
}
/*将接受的消息显示在消息窗口*/
void showMessage(char *message,textView *textViewAll)
{

        GtkTextIter start,end;
	GdkPixbuf *pixbuf;

	char content[1024];
	char time[30];
	char *name;
	char *delim = "#";
	char *ptr;
	char *text;
	char *filename;
	ptr = strstr(message,delim);
	text = strtok(message,delim);
	filename = strtok(NULL,delim);
	name = textViewAll->name;
        getSystemTime(time);
	if(ptr == NULL)
	{
printf("ptr == NULL\n");
		sprintf(content,"%s %s %s\n%s\n",name,time,":",text);
		gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(textViewAll->buffer1),&start,&end);
		gtk_text_buffer_insert(GTK_TEXT_BUFFER(textViewAll->buffer1),&end,content,-1);
	}
	else
	{
		if(strcmp(ptr,message)==0)
		{
			sprintf(content,"%s %s %s\n",name,time,":");
	
g_print("%s\n",content);

			gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(textViewAll->buffer1),&start,&end);
			gtk_text_buffer_insert(GTK_TEXT_BUFFER(textViewAll->buffer1),&end,content,-1);

			gtk_text_buffer_get_end_iter(textViewAll->buffer1,&end);
			pixbuf = gdk_pixbuf_new_from_file(text,NULL);
	
			gtk_text_buffer_insert_pixbuf(textViewAll->buffer1,&end,pixbuf);
			gtk_text_buffer_get_end_iter(textViewAll->buffer1,&end);
			gtk_text_buffer_insert(GTK_TEXT_BUFFER(textViewAll->buffer1),&end,"\n",-1);

g_print("%s\n","RECIEVE");
		}
//printf("ptr != NULL\n");
		else
		{
			sprintf(content,"%s %s %s\n%s",name,time,":",text);
	
g_print("%s\n",content);

			gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(textViewAll->buffer1),&start,&end);
			gtk_text_buffer_insert(GTK_TEXT_BUFFER(textViewAll->buffer1),&end,content,-1);

			gtk_text_buffer_get_end_iter(textViewAll->buffer1,&end);
			pixbuf = gdk_pixbuf_new_from_file(filename,NULL);
	
			gtk_text_buffer_insert_pixbuf(textViewAll->buffer1,&end,pixbuf);
			gtk_text_buffer_get_end_iter(textViewAll->buffer1,&end);
			gtk_text_buffer_insert(GTK_TEXT_BUFFER(textViewAll->buffer1),&end,"\n",-1);

g_print("%s\n","RECIEVE");
		}
	}

}
/*¹Ø±ÕÖ÷Ž°ÌåµÄ»Øµ÷º¯Êý*/
void closeApp ( GtkWidget *window,ip_window *ip_window_main)
{
  printf("------------!close\n");
  setOffTextView(ip_window_main->ip);
  gtk_widget_destroy(ip_window_main->window);
}

/*È¡Ïû°ŽÅ¥µÄ»Øµ÷º¯Êý*/
void undo ( GtkWidget *window, textView *textViewAll)
{
  gtk_text_buffer_set_text(textViewAll->buffer2,"",-1);
}

void chatRecordOk ( GtkWidget *button, gpointer data)
{
  show_record(data);
}

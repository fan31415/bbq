#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include  <gdk/gdkkeysyms.h>
#include "chatWindow.h"
/**************************************************/
/*Ãû³Æ£ºfontSelect
/*ÃèÊö£ºžüžÄ×ÖÌå»Øµ÷º¯Êý
/*×÷³ÉÈÕÆÚ£º 2010-07-01
/*²ÎÊý£º
         ²ÎÊý1£ºbutton¡¢GtkWidget*¡¢Á¬œÓ»Øµ÷º¯ÊýµÄ¿ØŒþ£¬×ÖÌå°ŽÅ¥
         ²ÎÊý2£ºdata¡¢gpointer¡¢»Øµ÷º¯ÊýŽ«ÈëµÄ²ÎÊý£¬ÉèÖÃNULL
/*·µ»ØÖµ£ºvoid
/*×÷Õß£ºÁõŸ°Ã÷¡ª¡ªteam5
/***************************************************/

/*×ÖÌåÑ¡ÔñÈ·ÈÏ°ŽÅ¥»Øµ÷º¯Êý*/
void font_selection_ok( GtkWidget *button, fontWindow_textView *fontWindow_textViewAll)
{

  GtkStyle *style;
  gchar *font;
  PangoFontDescription *font_desc;
 
  font = gtk_font_selection_dialog_get_font_name (GTK_FONT_SELECTION_DIALOG (fontWindow_textViewAll->window));

  font_desc = pango_font_description_from_string (font);
	
  style = gtk_style_copy (gtk_widget_get_style (fontWindow_textViewAll->textViewAll->textView2));

  style->font_desc = font_desc;

  gtk_widget_set_style (fontWindow_textViewAll->textViewAll->textView2, style);
  gtk_widget_set_style (fontWindow_textViewAll->textViewAll->textView1, style);

  gtk_widget_destroy(GTK_OBJECT(fontWindow_textViewAll->window));
  g_print("font_ok");
}

/*×ÖÌåÑ¡Ôñ°ŽÅ¥»Øµ÷º¯Êý,ŽŽœš×ÖÌåÑ¡Ôñ¿ò*/
void fontSelect( GtkWidget *button, textView *textViewAll)
{

    GtkWidget *window;

    window = gtk_font_selection_dialog_new ("Linpop v1.0 字体选择");

    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);

    fontWindow_textView *fontWindow_textViewAll = (fontWindow_textView *)malloc(sizeof(fontWindow_textView));
    fontWindow_textViewAll->window = window;
    fontWindow_textViewAll->textViewAll = textViewAll;

    g_signal_connect (G_OBJECT (GTK_FONT_SELECTION_DIALOG (window)->ok_button),
		      "clicked", G_CALLBACK (font_selection_ok),
		      fontWindow_textViewAll);

    g_signal_connect (G_OBJECT (window), "destroy",
	              G_CALLBACK (gtk_widget_destroyed),
		      NULL);

    gtk_signal_connect_object(GTK_OBJECT (GTK_FONT_SELECTION_DIALOG (window)->cancel_button),
			      "clicked",
			      GTK_SIGNAL_FUNC(gtk_widget_destroy), 
			      GTK_OBJECT(window));

    gtk_widget_show (window);

    g_print("font");

}

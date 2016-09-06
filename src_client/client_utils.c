/*
** client_utils.c for client_utils in /home/barre_v/rendu/PSU_2013_myirc/src_client
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Wed Apr 23 21:25:55 2014 barre_v
** Last update Sun Apr 27 18:38:27 2014 lamy_a
*/

#include	"client.h"

extern int		g_exit;

void			gtk_textview_append_color(GtkTextView *textview,
						  const char *line,
						  const char *color)
{
  GtkTextBuffer		*buffer;
  GtkTextMark		*mark;
  GtkTextIter		iter;

  if (g_exit)
    return ;
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
  mark = gtk_text_buffer_get_insert(buffer);
  gtk_text_buffer_get_end_iter(buffer, &iter);
  gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, line, -1,
					   color, NULL);
  mark = gtk_text_buffer_get_insert(buffer);
  gtk_text_buffer_get_iter_at_mark(buffer, &iter, mark);
  gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW(textview), mark);

}

void			gtk_textview_append(GtkTextView *textview,
					    const char *line)
{
  GtkTextBuffer		*buffer;
  GtkTextMark		*mark;
  GtkTextIter		iter;

  if (g_exit)
    return ;
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
  mark = gtk_text_buffer_get_insert(buffer);
  gtk_text_buffer_get_end_iter(buffer, &iter);
  gtk_text_buffer_insert(buffer, &iter, line, -1);
  mark = gtk_text_buffer_get_insert(buffer);
  gtk_text_buffer_get_iter_at_mark(buffer, &iter, mark);
  gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW(textview), mark);
}

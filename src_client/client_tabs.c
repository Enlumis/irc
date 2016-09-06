/*
** client_tabs.c for client_tabs in /home/barre_v/rendu/PSU_2013_myirc/src_client
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Wed Apr 23 18:20:03 2014 barre_v
** Last update Sun Apr 27 22:05:53 2014 barre_v
*/

#include	<gtk/gtk.h>
#include	<stdlib.h>
#include	"client.h"

extern t_channel	*g_channellist;
extern t_client		g_client;

static t_channel	*init_new_channel(int cid, char *cname)
{
  t_channel		*channel;

  printf("[Client-System] : Create channel `%s` with id `%d`\n", cname, cid);
  if ((channel = malloc(sizeof(t_channel))) == NULL)
    return (NULL);
  channel->next = NULL;
  channel->id = cid;
  sprintf(channel->name, "%s", cname);
  if (g_channellist != NULL)
    channel->next = g_channellist;
  g_channellist = channel;
  return (channel);
}

static GtkWidget	*client_add_main_container(t_channel *channel)
{
  GtkWidget		*container;
  GtkTextBuffer		*buf;

  container = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(container),
				 GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  channel->text_view = GTK_TEXT_VIEW(gtk_text_view_new());
  buf = gtk_text_view_get_buffer(channel->text_view);
  gtk_text_buffer_create_tag(buf, "#000000", "foreground", "#000000", NULL);
  gtk_text_buffer_create_tag(buf, "#0000FF", "foreground", "#0000FF", NULL);
  gtk_text_buffer_create_tag(buf, "#FF0000", "foreground", "#FF0000", NULL);
  gtk_text_buffer_create_tag(buf, "#CC00CC", "foreground", "#CC00CC", NULL);
  gtk_text_view_set_left_margin(channel->text_view, 10);
  gtk_text_view_set_right_margin(channel->text_view, 10);
  gtk_text_view_set_wrap_mode(channel->text_view, GTK_WRAP_CHAR);
  gtk_text_view_set_editable(channel->text_view, FALSE);
  gtk_container_add(GTK_CONTAINER(container), GTK_WIDGET(channel->text_view));
  gtk_widget_set_can_focus(GTK_WIDGET(channel->text_view), FALSE);
  return (container);
}

static GtkWidget	*client_add_user_list(t_channel *channel)
{
  GtkWidget		*container;

  container = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(container),
				 GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  channel->list_user = gtk_list_new();
  channel->users = NULL;
  gtk_list_insert_items(GTK_LIST(channel->list_user), channel->users, 0);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(container),
					channel->list_user);
  return (container);
}

static GtkWidget	*client_add_entry(t_channel *channel)
{
  GtkWidget		*entry;

  entry = gtk_entry_new_with_max_length(MESSAGE_MAX_SIZE);
  gtk_entry_set_activates_default(GTK_ENTRY(entry), TRUE);
  g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(on_enter), channel);
  gtk_widget_set_can_focus(entry, TRUE);
  channel->entry = GTK_ENTRY(entry);
  return (entry);
}

int		construct_onglet(GtkWidget *nb, char *cname, int cid)
{
  t_channel	*channel;
  GtkWidget	*vframe;
  GtkWidget	*hframe;
  GtkWidget	*entry;
  GtkWidget	*maincontainer;
  GtkWidget	*usercontainer;

  vframe = gtk_vbox_new(FALSE, 0);
  hframe = gtk_hbox_new(FALSE, 0);
  if ((channel = init_new_channel(cid, cname)) == NULL)
    return (1);
  maincontainer = client_add_main_container(channel);
  usercontainer = client_add_user_list(channel);
  entry = client_add_entry(channel);
  gtk_box_pack_start(GTK_BOX(hframe), vframe, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hframe), usercontainer, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vframe), maincontainer, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vframe), entry, FALSE, TRUE, 0);
  channel->page = hframe;
  gtk_notebook_append_page(GTK_NOTEBOOK(nb), hframe, gtk_label_new(cname));
  gtk_widget_show_all(nb);
  gtk_notebook_set_current_page(GTK_NOTEBOOK(nb), -1);
  gtk_widget_grab_focus(GTK_WIDGET(entry));
  return (0);
}

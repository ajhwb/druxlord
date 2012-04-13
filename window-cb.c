#include <gtk/gtk.h>
#include "window.h"
#include "druxlord.h"

gboolean
window_main_window_delete_event_cb (GtkWidget *widget,
                                    GdkEvent *event,
                                    gpointer data)
{
  gtk_main_quit ();
  return FALSE;
}

void
window_main_button_buy_clicked_cb (GtkWidget *widget,
                                   gpointer data)
{
  create_window_input ("input", "message", "how many?");
  gtk_widget_show_all (window_input.window);
}

void
window_main_button_places_clicked_cb (GtkWidget *widget,
                                      gpointer data)
{
  static GtkWidget *menu = NULL;

  if (!menu)
    menu = create_places_menu ();
  gtk_menu_popup (GTK_MENU (menu), NULL, NULL, NULL, NULL, 0, 
                  gtk_get_current_event_time ());
}

void
window_main_button_info_clicked_cb (GtkWidget *widget,
                                    gpointer data)
{
  static GtkWidget *menu = NULL;

  if (!menu)
    menu = create_info_menu ();
  gtk_menu_popup (GTK_MENU (menu), NULL, NULL, NULL, NULL, 0,
                  gtk_get_current_event_time ());
}

void
window_main_button_stayhere_clicked_cb (GtkWidget *widget,
                                        gpointer data)
{
  generate_drug ();
  insert_treeview_drug (GTK_TREE_VIEW (window_main.treeview_market));
}

void
menuitem_places_finances_activate_cb (GtkWidget *widget,
                                      gpointer data)
{
  create_window_finance ();
  gtk_widget_show_all (window_finance.window);
}

void
menuitem_places_shopping_activate_cb (GtkWidget *widget,
                                      gpointer data)
{
  create_window_shopping ();
  gtk_widget_show_all (window_shopping.window);
}

void
menuitem_places_hospital_activate_cb (GtkWidget *widget,
                                      gpointer data)
{
  create_window_hospital ();
  gtk_widget_show_all (window_hospital.window);
}

void
menuitem_places_vault_activate_cb (GtkWidget *widget,
                                   gpointer data)
{
  create_window_vault ();
  gtk_widget_show_all (window_vault.window);
}

void
menuitem_places_shipping_activate_cb (GtkWidget *widget,
                                      gpointer data)
{
}

void
menuitem_info_vaults_activate_cb (GtkWidget *widget,
                                  gpointer data)
{
}

void
menuitem_info_drug_prices_activate_cb (GtkWidget *widget,
                                       gpointer data)
{
}

void
menuitem_info_world_cities_activate_cb (GtkWidget *widget,
                                        gpointer data)
{
}

void
menuitem_info_shipment_status_activate_cb (GtkWidget *widget,
                                           gpointer data)
{
}

void
menuitem_info_history_activate_cb (GtkWidget *widget,
                                   gpointer data)
{
}

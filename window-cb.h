#ifndef __WINDOW_CB_H__
#define __WINDOW_CB_H__

#include <gtk/gtk.h>

gboolean
window_main_window_delete_event_cb (GtkWidget *widget,
                                    GdkEvent *event,
                                    gpointer data);

void
window_main_button_buy_clicked_cb (GtkWidget *widget,
                                   gpointer data);

void
window_main_button_places_clicked_cb (GtkWidget *widget,
                                      gpointer data);

void
window_main_button_info_clicked_cb (GtkWidget *widget,
                                    gpointer data);

void
window_main_button_stayhere_clicked_cb (GtkWidget *widget,
                                        gpointer data);

void
menuitem_places_finances_activate_cb (GtkWidget *widget,
                                      gpointer data);

void
menuitem_places_shopping_activate_cb (GtkWidget *widget,
                                      gpointer data);

void
menuitem_places_hospital_activate_cb (GtkWidget *widget,
                                      gpointer data);

void
menuitem_places_vault_activate_cb (GtkWidget *widget,
                                   gpointer data);

void
menuitem_places_shipping_activate_cb (GtkWidget *widget,
                                      gpointer data);

void
menuitem_info_vaults_activate_cb (GtkWidget *widget,
                                  gpointer data);

void
menuitem_info_drug_prices_activate_cb (GtkWidget *widget,
                                       gpointer data);

void
menuitem_info_world_cities_activate_cb (GtkWidget *widget,
                                        gpointer data);

void
menuitem_info_shipment_status_activate_cb (GtkWidget *widget,
                                           gpointer data);

void
menuitem_info_history_activate_cb (GtkWidget *widget,
                                   gpointer data);
#endif

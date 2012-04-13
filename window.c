#include <gtk/gtk.h>
#include "window.h"
#include "window-cb.h"
#include "config.h"
#include "druxlord.h"

#define COLUMN_NAME_WIDTH   120
#define COLUMN_QTY_WIDTH    50
#define COLUMN_PRICE_WIDTH  70

void
insert_treeview_drug (GtkTreeView *treeview)
{
  GtkTreeIter iter;
  GtkTreeModel *model = gtk_tree_view_get_model (treeview);
  gint i, j = 0;
  gchar *tmp;

  gtk_list_store_clear (GTK_LIST_STORE (model));

  for (i = 0; i < DRUG_NUM; i++)
    if (drug_table[i][j].available)
      {
        tmp = money_string (drug_table[i][j].price);
        gtk_list_store_append (GTK_LIST_STORE (model), &iter);
        gtk_list_store_set (GTK_LIST_STORE (model), &iter, 
                            COLUMN_NAME, drug_name[i], 
                            COLUMN_QTY, drug_table[i][j].qty,
                            COLUMN_PRICE, tmp, -1);
        g_free (tmp);
      }
}

static GtkWidget*
create_treeview_drug (gboolean with_status)
{
  GtkWidget *treeview;
  GtkListStore *store;
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;

  treeview = gtk_tree_view_new ();

  if (with_status)
    store = gtk_list_store_new (4, GDK_TYPE_PIXBUF, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING);
  else
    store = gtk_list_store_new (3, G_TYPE_STRING, G_TYPE_INT, G_TYPE_LONG);
  gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), 
                           GTK_TREE_MODEL (store));

  if (with_status)
    {
      renderer = gtk_cell_renderer_pixbuf_new ();
      column = gtk_tree_view_column_new_with_attributes ("", renderer,
                                                         "pixbuf", COLUMN_STATUS, NULL);
      gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);
    }

  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("Name", renderer,
                                                     "text", COLUMN_NAME, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 120);
  gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Qty", renderer,
                                                     "text", COLUMN_QTY, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 50);
  gtk_tree_view_column_set_alignment (column, 0.9);
  gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Price", renderer,
                                                     "text", COLUMN_PRICE, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 70);
  gtk_tree_view_column_set_alignment (column, 0.9);
  gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

  return treeview;
}

void
set_label_frame_pocket (gint npocket)
{
  gchar *tmp;

  tmp = g_strdup_printf ("You pants pocket (%i/10)", npocket);
  gtk_label_set_text (GTK_LABEL (window_main.label_pocket), tmp);
  g_free (tmp);
}

void
set_label_location (int location)
{
  gchar *markup;
  const gchar * const location_str[] = { "Austin, US" };

  markup = g_strdup_printf ("<span><b>%s</b></span>", location_str[0]);
  gtk_label_set_markup (GTK_LABEL (window_main.label_location), markup);
  g_free (markup);
}

void
set_label_day (gint day)
{
  gchar *markup;

  markup = g_strdup_printf ("<span><b>%i/30</b></span>", day);
  gtk_label_set_markup (GTK_LABEL (window_main.label_day), markup);
  g_free (markup);
}

void
set_label_rank (gint rank)
{
  gchar *markup;
  const gchar * const rank_str[] = { "wannabe" };

  markup = g_strdup_printf ("<span><b>%s</b></span>", rank_str[0]);
  gtk_label_set_markup (GTK_LABEL (window_main.label_rank), markup);
  g_free (markup);
}

void
set_label_cash (gint value)
{
  gchar *markup;

  markup = g_strdup_printf ("<span><b>%i</b></span>", value);
  gtk_label_set_markup (GTK_LABEL (window_main.label_cash), markup);
  g_free (markup);
}

void
set_label_bank (gint value)
{
  gchar *markup;

  markup = g_strdup_printf ("<span><b>%i</b></span>", value);
  gtk_label_set_markup (GTK_LABEL (window_main.label_bank), markup);
  g_free (markup);
}

void
set_label_debt (gint value)
{
  gchar *markup;

  if (value > 0)
    markup = g_strdup_printf ("<span foreground=\"#FF0000\"><b>%i</b></span>", value);
  else
    markup = g_strdup_printf ("<span><b>%i</b></span>", value);
  gtk_label_set_markup (GTK_LABEL (window_main.label_debt), markup);
  g_free (markup);
}

void
create_window_main ()
{
  GtkWidget *frame;
  GtkWidget *vbox_main;
  GtkWidget *hbox_down;
  GtkWidget *vbox;
  GtkWidget *box, *box2;
  GtkWidget *scrolled_window;
  GtkWidget *label;
  gchar *tmp;

  window_main.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window_main.window), PROGRAM_NAME);
  gtk_window_set_resizable (GTK_WINDOW (window_main.window), FALSE);
  gtk_window_set_position (GTK_WINDOW (window_main.window), GTK_WIN_POS_CENTER_ALWAYS);
  g_signal_connect (window_main.window, "delete-event", 
                    G_CALLBACK (window_main_window_delete_event_cb), NULL);

  vbox_main = gtk_vbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (vbox_main), 5);
  gtk_container_add (GTK_CONTAINER (window_main.window), vbox_main);

  frame = gtk_frame_new ("Information");
  gtk_box_pack_start (GTK_BOX (vbox_main), frame, FALSE, TRUE, 0);

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_NEVER,
                                  GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window),
                                       GTK_SHADOW_IN);
  gtk_widget_set_size_request (scrolled_window, -1, 120);
  gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 5);
  gtk_container_add (GTK_CONTAINER (frame), scrolled_window);

  window_main.textview_information = gtk_text_view_new ();
  gtk_text_view_set_editable (GTK_TEXT_VIEW (window_main.textview_information), FALSE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), window_main.textview_information);


  hbox_down = gtk_hbox_new (FALSE, 8);
  gtk_box_pack_start (GTK_BOX (vbox_main), hbox_down, FALSE, TRUE, 0);


  frame = gtk_frame_new ("The Market");
  gtk_box_pack_start (GTK_BOX (hbox_down), frame, FALSE, TRUE, 0);

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_NEVER,
                                  GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window),
                                       GTK_SHADOW_IN);
  gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 5);
  gtk_container_add (GTK_CONTAINER (frame), scrolled_window);

  window_main.treeview_market = create_treeview_drug (TRUE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), window_main.treeview_market);


  vbox = gtk_vbox_new (FALSE, 5);
  gtk_box_pack_start (GTK_BOX (hbox_down), vbox, FALSE, TRUE, 0);


  frame = gtk_frame_new ("Action");
  gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);

  box = gtk_vbox_new (FALSE, 3);
  gtk_container_set_border_width (GTK_CONTAINER (box), 5);
  gtk_container_add (GTK_CONTAINER (frame), box);

  tmp = g_strdup ("_Buy \342\206\222");
  window_main.button_buy = gtk_button_new_with_mnemonic (tmp);
  g_free (tmp);
  gtk_box_pack_start (GTK_BOX (box), window_main.button_buy, FALSE, TRUE, 0);
  g_signal_connect (window_main.button_buy, "clicked",
                    G_CALLBACK (window_main_button_buy_clicked_cb), NULL);

  tmp = g_strdup ("\342\206\220 _Sell");
  window_main.button_sell = gtk_button_new_with_mnemonic (tmp);
  g_free (tmp);
  gtk_box_pack_start (GTK_BOX (box), window_main.button_sell, FALSE, TRUE, 0);

  window_main.button_dump = gtk_button_new_with_mnemonic ("_Dump");
  gtk_box_pack_start (GTK_BOX (box), window_main.button_dump, FALSE, TRUE, 0);

  window_main.button_places = gtk_button_new_with_mnemonic ("Places...");
  g_signal_connect (window_main.button_places, "clicked",
                    G_CALLBACK (window_main_button_places_clicked_cb), NULL);
  gtk_box_pack_start (GTK_BOX (box), window_main.button_places, FALSE, TRUE, 0);

  window_main.button_info = gtk_button_new_with_mnemonic ("Info...");
  g_signal_connect (window_main.button_info, "clicked",
                    G_CALLBACK (window_main_button_info_clicked_cb), NULL);
  gtk_box_pack_start (GTK_BOX (box), window_main.button_info, FALSE, TRUE, 0);


  frame = gtk_frame_new ("Tomorrow");
  gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);

  box = gtk_vbox_new (FALSE, 3);
  gtk_container_set_border_width (GTK_CONTAINER (box), 5);
  gtk_container_add (GTK_CONTAINER (frame), box);

  window_main.button_stayhere = gtk_button_new_with_mnemonic ("Stay Here");
  g_signal_connect (window_main.button_stayhere, "clicked",
                    G_CALLBACK (window_main_button_stayhere_clicked_cb), NULL);
  gtk_box_pack_start (GTK_BOX (box), window_main.button_stayhere, FALSE, TRUE, 0);

  window_main.button_flyaway = gtk_button_new_with_mnemonic ("Fly Away");
  gtk_box_pack_start (GTK_BOX (box), window_main.button_flyaway, FALSE, TRUE, 0);


  frame = gtk_frame_new ("Game");
  gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);

  box = gtk_vbox_new (FALSE, 3);
  gtk_container_set_border_width (GTK_CONTAINER (box), 5);
  gtk_container_add (GTK_CONTAINER (frame), box);

  window_main.checkbutton_sound = gtk_check_button_new_with_mnemonic ("Sou_nd");
  gtk_box_pack_start (GTK_BOX (box), window_main.checkbutton_sound, FALSE, TRUE, 0);

  window_main.button_about = gtk_button_new_with_mnemonic ("_About");
  gtk_box_pack_start (GTK_BOX (box), window_main.button_about, FALSE, TRUE, 0);

  window_main.button_docs = gtk_button_new_with_mnemonic ("Docs");
  gtk_box_pack_start (GTK_BOX (box), window_main.button_docs, FALSE, TRUE, 0);

  window_main.button_highscores = gtk_button_new_with_mnemonic ("High Scores");
  gtk_box_pack_start (GTK_BOX (box), window_main.button_highscores, FALSE, TRUE, 0);

  window_main.button_newgamequit = gtk_button_new_with_mnemonic ("New _Game");
  gtk_box_pack_start (GTK_BOX (box), window_main.button_newgamequit, FALSE, TRUE, 0);


  vbox = gtk_vbox_new (FALSE, 5);
  gtk_box_pack_start (GTK_BOX (hbox_down), vbox, FALSE, TRUE, 0);


  frame = gtk_frame_new ("");
  gtk_container_add (GTK_CONTAINER (vbox), frame);

  window_main.label_pocket = gtk_label_new (NULL);
  set_label_frame_pocket (0);
  gtk_frame_set_label_widget (GTK_FRAME (frame), window_main.label_pocket);

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_NEVER,
                                  GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window),
                                       GTK_SHADOW_IN);
  gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 5);
  gtk_container_add (GTK_CONTAINER (frame), scrolled_window);

  window_main.treeview_pocket = create_treeview_drug (FALSE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), window_main.treeview_pocket);


  frame = gtk_frame_new ("Status");
  gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, TRUE, 0);

  vbox = gtk_vbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), vbox);

  box = gtk_hbox_new (FALSE, 10);
  gtk_box_pack_start (GTK_BOX (vbox), box, FALSE, TRUE, 0);

  label = gtk_label_new ("Location:");
  gtk_box_pack_start (GTK_BOX (box), label, FALSE, TRUE, 0);

  window_main.label_location = gtk_label_new (NULL);
  gtk_label_set_use_markup (GTK_LABEL (window_main.label_location), TRUE);
  gtk_box_pack_start (GTK_BOX (box), window_main.label_location, FALSE, TRUE, 0);
  set_label_location (0);

  box = gtk_hbox_new (FALSE, 10);
  gtk_box_pack_start (GTK_BOX (vbox), box, FALSE, TRUE, 0);

  label = gtk_label_new ("Health:");
  gtk_box_pack_start (GTK_BOX (box), label, FALSE, TRUE, 0);

  window_main.progressbar_health = gtk_progress_bar_new ();
  gtk_box_pack_start (GTK_BOX (box), window_main.progressbar_health, TRUE, TRUE, 0);

  box = gtk_hbox_new (FALSE, 30);
  gtk_box_pack_start (GTK_BOX (vbox), box, FALSE, TRUE, 0);

  box2 = gtk_hbox_new (FALSE, 10);
  gtk_box_pack_start (GTK_BOX (box), box2, FALSE, TRUE, 0);

  label = gtk_label_new ("Day:");
  gtk_box_pack_start (GTK_BOX (box2), label, FALSE, TRUE, 0);

  window_main.label_day = gtk_label_new (NULL);
  gtk_label_set_use_markup (GTK_LABEL (window_main.label_day), TRUE);
  set_label_day (0);
  gtk_box_pack_start (GTK_BOX (box2), window_main.label_day, FALSE, TRUE, 0);

  box2 = gtk_hbox_new (FALSE, 10);
  gtk_box_pack_start (GTK_BOX (box), box2, FALSE, TRUE, 0);

  label = gtk_label_new ("Rank:");
  gtk_box_pack_start (GTK_BOX (box2), label, FALSE, TRUE, 0);

  window_main.label_rank = gtk_label_new (NULL);
  gtk_label_set_use_markup (GTK_LABEL (window_main.label_rank), TRUE);
  set_label_rank (0);
  gtk_box_pack_start (GTK_BOX (box2), window_main.label_rank, FALSE, TRUE, 0);


  box = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), box, FALSE, TRUE, 0);

  box2 = gtk_table_new (3, 2, FALSE);
  gtk_table_set_row_spacings (GTK_TABLE (box2), 5);
  gtk_table_set_col_spacings (GTK_TABLE (box2), 50);
  gtk_box_pack_start (GTK_BOX (box), box2, FALSE, TRUE, 0);

  label = gtk_label_new ("Cash:");
  gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
  gtk_table_attach_defaults (GTK_TABLE (box2), label, 0, 1, 0, 1);

  window_main.label_cash = gtk_label_new (NULL);
  gtk_label_set_use_markup (GTK_LABEL (window_main.label_cash), TRUE);
  gtk_misc_set_alignment (GTK_MISC (window_main.label_cash), 1.0, 0.5);
  set_label_cash (1900);
  gtk_table_attach_defaults (GTK_TABLE (box2), window_main.label_cash, 1, 2, 0, 1);


  label = gtk_label_new ("Bank:");
  gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
  gtk_table_attach_defaults (GTK_TABLE (box2), label, 0, 1, 1, 2);

  window_main.label_bank = gtk_label_new (NULL);
  gtk_label_set_use_markup (GTK_LABEL (window_main.label_bank), TRUE);
  gtk_misc_set_alignment (GTK_MISC (window_main.label_bank), 1.0, 0.5);
  set_label_bank (0);
  gtk_table_attach_defaults (GTK_TABLE (box2), window_main.label_bank, 1, 2, 1, 2);


  label = gtk_label_new ("Debt:");
  gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
  gtk_table_attach_defaults (GTK_TABLE (box2), label, 0, 1, 2, 3);

  window_main.label_debt = gtk_label_new (NULL);
  gtk_label_set_use_markup (GTK_LABEL (window_main.label_debt), TRUE);
  gtk_misc_set_alignment (GTK_MISC (window_main.label_debt), 1.0, 0.5);
  set_label_debt (0);
  gtk_table_attach_defaults (GTK_TABLE (box2), window_main.label_debt, 1, 2, 2, 3);

  window_main.drawingarea_status = gtk_drawing_area_new ();
  gtk_container_add (GTK_CONTAINER (box), window_main.drawingarea_status);
}

void
create_window_finance ()
{
  GtkWidget *vbox_main;
  GtkWidget *vbox, *hbox, *hbox2;
  GtkWidget *table;
  GtkWidget *frame;
  GtkWidget *label;
  GtkWidget *scrolled_window;
  GtkListStore *store;
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;

  window_finance.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window_finance.window), "Finance");
  gtk_window_set_type_hint (GTK_WINDOW (window_finance.window), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_window_set_transient_for (GTK_WINDOW (window_finance.window),
                                GTK_WINDOW (window_main.window));
  gtk_window_set_modal (GTK_WINDOW (window_finance.window), TRUE);
  gtk_window_set_resizable (GTK_WINDOW (window_finance.window), FALSE);
  g_signal_connect_swapped (window_finance.window, "destroy", 
                            G_CALLBACK (gtk_widget_destroy), window_finance.window);

  vbox_main = gtk_vbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (vbox_main), 5);
  gtk_container_add (GTK_CONTAINER (window_finance.window), vbox_main);

  frame = gtk_frame_new ("Bank");
  gtk_box_pack_start (GTK_BOX (vbox_main), frame, FALSE, TRUE, 0);

  vbox = gtk_vbox_new (FALSE, 3);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), vbox);

  hbox = gtk_hbox_new (FALSE, 130);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 0);

  hbox2 = gtk_hbox_new (FALSE, 20);
  gtk_box_pack_start (GTK_BOX (hbox), hbox2, FALSE, TRUE, 0);

  label = gtk_label_new ("Cash:");
  gtk_box_pack_start (GTK_BOX (hbox2), label, FALSE, TRUE, 0);

  window_finance.label_cash = gtk_label_new ("0");
  gtk_box_pack_start (GTK_BOX (hbox2), window_finance.label_cash, FALSE, TRUE, 0);

  hbox2 = gtk_hbox_new (FALSE, 20);
  gtk_box_pack_start (GTK_BOX (hbox), hbox2, FALSE, TRUE, 0);

  label = gtk_label_new ("In Bank:");
  gtk_box_pack_start (GTK_BOX (hbox2), label, FALSE, TRUE, 0);

  window_finance.label_bank = gtk_label_new ("0");
  gtk_box_pack_start (GTK_BOX (hbox2), window_finance.label_bank, FALSE, TRUE, 0);

  table = gtk_table_new (2, 3, FALSE);
  gtk_table_set_col_spacings (GTK_TABLE (table), 3);
  gtk_table_set_row_spacings (GTK_TABLE (table), 3);
  gtk_box_pack_start (GTK_BOX (vbox), table, FALSE, TRUE, 0);

  window_finance.radiobutton_depositsome = gtk_radio_button_new_with_label (NULL, "Deposit some");
  gtk_table_attach_defaults (GTK_TABLE (table), window_finance.radiobutton_depositsome, 0, 1, 0, 1);

  window_finance.radiobutton_depositall = 
    gtk_radio_button_new_with_label_from_widget 
        (GTK_RADIO_BUTTON (window_finance.radiobutton_depositsome), "Deposit all");
  gtk_table_attach_defaults (GTK_TABLE (table), window_finance.radiobutton_depositall, 1, 2, 0, 1);

  window_finance.radiobutton_depositallbut = 
    gtk_radio_button_new_with_label_from_widget 
        (GTK_RADIO_BUTTON (window_finance.radiobutton_depositsome), "Deposit all but");
  gtk_table_attach_defaults (GTK_TABLE (table), window_finance.radiobutton_depositallbut, 2, 3, 0, 1);

  window_finance.radiobutton_withdrawsome =
    gtk_radio_button_new_with_label_from_widget 
      (GTK_RADIO_BUTTON (window_finance.radiobutton_depositsome), "Withdraw some");
  gtk_table_attach_defaults (GTK_TABLE (table), window_finance.radiobutton_withdrawsome, 0, 1, 1, 2);

  window_finance.radiobutton_withdrawall = 
    gtk_radio_button_new_with_label_from_widget 
        (GTK_RADIO_BUTTON (window_finance.radiobutton_depositsome), "Withdraw all");
  gtk_table_attach_defaults (GTK_TABLE (table), window_finance.radiobutton_withdrawall, 1, 2, 1, 2);

  window_finance.radiobutton_withdrawallbut = 
    gtk_radio_button_new_with_label_from_widget 
        (GTK_RADIO_BUTTON (window_finance.radiobutton_depositsome), "Withdraw all but");
  gtk_table_attach_defaults (GTK_TABLE (table), window_finance.radiobutton_withdrawallbut, 2, 3, 1, 2);

  hbox = gtk_hbox_new (FALSE, 10);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 0);

  label = gtk_label_new ("Amount");
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, TRUE, 0);

  window_finance.spinbutton_amount = gtk_spin_button_new_with_range (1.0, 1000000000.0, 1.0);
  gtk_box_pack_start (GTK_BOX (hbox), window_finance.spinbutton_amount, FALSE, TRUE, 0);

  window_finance.button_doit = gtk_button_new_with_label ("Do it!");
  gtk_box_pack_start (GTK_BOX (hbox), window_finance.button_doit, FALSE, TRUE, 0);

  frame = gtk_frame_new ("Loans");
  gtk_container_add (GTK_CONTAINER (vbox_main), frame);

  vbox = gtk_vbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), vbox);

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_NEVER,
                                  GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window),
                                       GTK_SHADOW_IN);
  gtk_widget_set_size_request (scrolled_window, -1, 170);
  gtk_container_add (GTK_CONTAINER (vbox), scrolled_window);

  store = gtk_list_store_new (6, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, 
                              G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);

  window_finance.treeview_loan = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
  gtk_container_add (GTK_CONTAINER (scrolled_window), window_finance.treeview_loan);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Name", renderer,
                                                     "text", COLUMN_LOAN_NAME, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 70);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_finance.treeview_loan ), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Pays", renderer,
                                                     "text", COLUMN_LOAN_PAY, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 70);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_finance.treeview_loan), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Rate", renderer,
                                                     "text", COLUMN_LOAN_RATE, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 70);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_finance.treeview_loan), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Days", renderer,
                                                     "text", COLUMN_LOAN_DAY, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 70);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_finance.treeview_loan), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Debt", renderer,
                                                     "text", COLUMN_LOAN_DEBT, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 70);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_finance.treeview_loan), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Days Left", renderer,
                                                     "text", COLUMN_LOAN_DAYLEFT, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 70);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_finance.treeview_loan), column);

  hbox = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 0);

  hbox2 = gtk_hbox_new (FALSE, 20);
  gtk_container_add (GTK_CONTAINER (hbox), hbox2);

  label = gtk_label_new ("Debt:");
  gtk_box_pack_start (GTK_BOX (hbox2), label, FALSE, TRUE, 0);

  window_finance.label_debt = gtk_label_new ("0");
  gtk_box_pack_start (GTK_BOX (hbox2), window_finance.label_debt, FALSE, TRUE, 0);

  hbox2 = gtk_hbox_new (FALSE, 3);
  gtk_box_pack_start (GTK_BOX (hbox), hbox2, FALSE, TRUE, 0);

  window_finance.button_borrow = gtk_button_new_with_label ("Borrow");
  gtk_container_add (GTK_CONTAINER (hbox2), window_finance.button_borrow);

  window_finance.button_repay = gtk_button_new_with_label ("Repay");
  gtk_container_add (GTK_CONTAINER (hbox2), window_finance.button_repay);

  hbox = gtk_hbutton_box_new ();
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbox), GTK_BUTTONBOX_END);
  gtk_box_pack_start (GTK_BOX (vbox_main), hbox, FALSE, TRUE, 0);

  window_finance.button_done = gtk_button_new_with_label ("Done");
  gtk_box_pack_end (GTK_BOX (hbox), window_finance.button_done, FALSE, TRUE, 0);
  g_signal_connect_swapped (window_finance.button_done, "clicked",
                            G_CALLBACK (gtk_widget_destroy), window_finance.window);
}

void
create_window_shopping ()
{
  GtkWidget *vbox_main, *vbox, *hbox, *hbox2;
  GtkWidget *frame;
  GtkWidget *scrolled_window;
  GtkWidget *label;
  GtkListStore *store;
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;

  window_shopping.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window_shopping.window), "Shopping");
  gtk_window_set_type_hint (GTK_WINDOW (window_shopping.window), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_window_set_transient_for (GTK_WINDOW (window_shopping.window),
                                GTK_WINDOW (window_main.window));
  gtk_window_set_modal (GTK_WINDOW (window_shopping.window), TRUE);
  gtk_window_set_resizable (GTK_WINDOW (window_shopping.window), FALSE);
  g_signal_connect_swapped (window_shopping.window, "destroy", 
                            G_CALLBACK (gtk_widget_destroy), window_shopping.window);

  vbox_main = gtk_vbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (vbox_main), 5);
  gtk_container_add (GTK_CONTAINER (window_shopping.window), vbox_main);

  frame = gtk_frame_new ("Store's Inventory");
  gtk_box_pack_start (GTK_BOX (vbox_main), frame, FALSE, TRUE, 0);

  vbox = gtk_vbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), vbox);

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_NEVER,
                                  GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window),
                                       GTK_SHADOW_IN);
  gtk_widget_set_size_request (scrolled_window, -1, 220);
  gtk_box_pack_start (GTK_BOX (vbox), scrolled_window, FALSE, TRUE, 0);

  store = gtk_list_store_new (3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
  window_shopping.treeview_store = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
  gtk_container_add (GTK_CONTAINER (scrolled_window), window_shopping.treeview_store);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Name", renderer,
                                                     "text", COLUMN_STORE_NAME, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 140);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_shopping.treeview_store), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Type", renderer,
                                                     "text", COLUMN_STORE_TYPE, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 100);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_shopping.treeview_store), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Price", renderer,
                                                     "text", COLUMN_STORE_PRICE, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 70);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_shopping.treeview_store), column);

  hbox = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 0);

  window_shopping.button_buy = gtk_button_new_with_label ("   Buy   ");
  gtk_box_pack_end (GTK_BOX (hbox), window_shopping.button_buy, FALSE, TRUE, 0);


  frame = gtk_frame_new ("Your Inventory");
  gtk_box_pack_start (GTK_BOX (vbox_main), frame, FALSE, TRUE, 0);

  vbox = gtk_vbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), vbox);

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_NEVER,
                                  GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window),
                                       GTK_SHADOW_IN);
  gtk_widget_set_size_request (scrolled_window, -1, 150);
  gtk_box_pack_start (GTK_BOX (vbox), scrolled_window, FALSE, TRUE, 0);

  store = gtk_list_store_new (3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);
  window_shopping.treeview_inventory = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
  gtk_container_add (GTK_CONTAINER (scrolled_window), window_shopping.treeview_inventory);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Name", renderer,
                                                     "text", COLUMN_INVENTORY_NAME, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 140);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_shopping.treeview_inventory), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Type", renderer,
                                                     "text", COLUMN_INVENTORY_TYPE, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 100);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_shopping.treeview_inventory), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Qty", renderer,
                                                     "text", COLUMN_INVENTORY_QTY, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 70);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_shopping.treeview_inventory), column);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_renderer_set_alignment (renderer, 0.9, 0.5);
  column = gtk_tree_view_column_new_with_attributes ("Price", renderer,
                                                     "text", COLUMN_INVENTORY_SELLFOR, NULL);
  gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_column_set_min_width (column, 70);
  gtk_tree_view_append_column (GTK_TREE_VIEW (window_shopping.treeview_inventory), column);

  hbox = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 0);

  hbox2 = gtk_hbox_new (FALSE, 20);
  gtk_container_add (GTK_CONTAINER (hbox), hbox2);

  label = gtk_label_new ("Cash:");
  gtk_box_pack_start (GTK_BOX (hbox2), label, FALSE, TRUE, 0);

  window_shopping.label_cash = gtk_label_new ("0");
  gtk_box_pack_start (GTK_BOX (hbox2), window_shopping.label_cash, FALSE, TRUE, 0);

  hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (hbox), hbox2, FALSE, TRUE, 0);

  window_shopping.button_sell = gtk_button_new_with_label ("   Sell   ");
  gtk_box_pack_end (GTK_BOX (hbox2), window_shopping.button_sell, FALSE, TRUE, 0);

  hbox = gtk_hbutton_box_new ();
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbox), GTK_BUTTONBOX_END);
  gtk_box_pack_start (GTK_BOX (vbox_main), hbox, FALSE, TRUE, 0);

  window_shopping.button_done = gtk_button_new_with_label ("Done");
  gtk_box_pack_end (GTK_BOX (hbox), window_shopping.button_done, FALSE, TRUE, 0);
  g_signal_connect_swapped (window_shopping.button_done, "clicked",
                            G_CALLBACK (gtk_widget_destroy), window_shopping.window);
}

void
create_window_hospital ()
{
  GtkWidget *image;
  GtkWidget *frame;
  GtkWidget *label;
  GtkWidget *vbox_main, *vbox, *vbox2, *hbox, *hbox2;
  GtkWidget *table;
  GtkWidget *button;

  window_hospital.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window_hospital.window), "Hospital");
  gtk_window_set_type_hint (GTK_WINDOW (window_hospital.window), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_window_set_transient_for (GTK_WINDOW (window_hospital.window),
                                GTK_WINDOW (window_main.window));
  gtk_window_set_modal (GTK_WINDOW (window_hospital.window), TRUE);
  gtk_window_set_resizable (GTK_WINDOW (window_hospital.window), FALSE);
  g_signal_connect_swapped (window_hospital.window, "destroy", 
                            G_CALLBACK (gtk_widget_destroy), window_hospital.window);

  vbox_main = gtk_vbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (vbox_main), 5);
  gtk_container_add (GTK_CONTAINER (window_hospital.window), vbox_main);

  hbox = gtk_hbox_new (FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vbox_main), hbox, FALSE, TRUE, 0);

  frame = gtk_frame_new ("");
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, TRUE, 0);

  hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox2), 20);
  gtk_container_add (GTK_CONTAINER (frame), hbox2);

  image = gtk_image_new_from_stock (GTK_STOCK_HELP, GTK_ICON_SIZE_DIALOG);
  gtk_box_pack_start (GTK_BOX (hbox2), image, FALSE, TRUE, 0);


  frame = gtk_frame_new ("Move the pointer to desired health");
  gtk_widget_set_size_request (frame, 400, -1);
  gtk_container_add (GTK_CONTAINER (hbox), frame);

  vbox = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), vbox);

  vbox2 = gtk_vbox_new (FALSE, 3);
  gtk_container_add (GTK_CONTAINER (vbox), vbox2);

  window_hospital.progressbar_health = gtk_progress_bar_new ();
  gtk_box_pack_start (GTK_BOX (vbox2), window_hospital.progressbar_health, FALSE, TRUE, 0);

  window_hospital.scalebutton_health = gtk_hscale_new_with_range (1.0, 100.0, 1.0);
  gtk_scale_set_draw_value (GTK_SCALE (window_hospital.scalebutton_health), FALSE);
  gtk_box_pack_start (GTK_BOX (vbox2), window_hospital.scalebutton_health, FALSE, TRUE, 0);

  vbox2 = gtk_vbox_new (FALSE, 3);
  gtk_box_pack_start (GTK_BOX (vbox), vbox2, FALSE, TRUE, 0);

  table = gtk_table_new (2, 2, FALSE);
  gtk_table_set_col_spacings (GTK_TABLE (table), 10);
  gtk_table_set_row_spacings (GTK_TABLE (table), 3);
  gtk_box_pack_start (GTK_BOX (vbox2), table, FALSE, TRUE, 0);

  label = gtk_label_new ("Cash:");
  gtk_misc_set_alignment (GTK_MISC (label), 1.0, 0.5);
  gtk_table_attach (GTK_TABLE (table), label, 0, 1, 0, 1,
                    GTK_FILL, 0, 0, 0);

  window_hospital.label_cash = gtk_label_new ("0");
  gtk_table_attach (GTK_TABLE (table), window_hospital.label_cash, 1, 2, 0, 1,
                    0, 0, 0, 0);

  label = gtk_label_new ("Cost for treatment:");
  gtk_misc_set_alignment (GTK_MISC (label), 1.0, 0.5);
  gtk_table_attach (GTK_TABLE (table), label, 0, 1, 1, 2,
                    GTK_FILL, 0, 0, 0);

  window_hospital.label_cost = gtk_label_new ("0");
  gtk_table_attach (GTK_TABLE (table), window_hospital.label_cost, 1, 2, 1, 2,
                    0, 0, 0, 0);

  hbox = gtk_hbutton_box_new ();
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbox), GTK_BUTTONBOX_END);
  gtk_box_set_spacing (GTK_BOX (hbox), 3);
  gtk_box_pack_end (GTK_BOX (vbox_main), hbox, FALSE, TRUE, 0);

  window_hospital.button_ok = gtk_button_new_with_mnemonic ("_OK");
  gtk_box_pack_start (GTK_BOX (hbox), window_hospital.button_ok, FALSE, TRUE, 0);

  button = gtk_button_new_with_mnemonic ("_Cancel");
  gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, TRUE, 0);
  g_signal_connect_swapped (button, "clicked",
                            G_CALLBACK (gtk_widget_destroy), window_hospital.window);
}

void
create_window_vault ()
{
  GtkWidget *frame;
  GtkWidget *scrolled_window;
  GtkWidget *vbox_main, *vbox, *hbox;
  GtkWidget *button;
  gchar *tmp;

  window_vault.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window_vault.window), "The Vault");
  gtk_window_set_type_hint (GTK_WINDOW (window_vault.window), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_window_set_transient_for (GTK_WINDOW (window_vault.window),
                                GTK_WINDOW (window_main.window));
  gtk_window_set_modal (GTK_WINDOW (window_vault.window), TRUE);
  gtk_window_set_resizable (GTK_WINDOW (window_vault.window), FALSE);
  g_signal_connect_swapped (window_vault.window, "destroy", 
                            G_CALLBACK (gtk_widget_destroy), window_vault.window);

  vbox_main = gtk_vbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (vbox_main), 5);
  gtk_container_add (GTK_CONTAINER (window_vault.window), vbox_main);

  hbox = gtk_hbox_new (FALSE, 5);
  gtk_box_pack_start (GTK_BOX (vbox_main), hbox, FALSE, TRUE, 0);

  frame = gtk_frame_new ("You pants pocket (0/10)");
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, TRUE, 0);

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_NEVER,
                                  GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window),
                                       GTK_SHADOW_IN);
  gtk_widget_set_size_request (scrolled_window, -1, 200);
  gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 5);
  gtk_container_add (GTK_CONTAINER (frame), scrolled_window);

  window_vault.treeview_pocket = create_treeview_drug (FALSE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), window_vault.treeview_pocket);

  frame = gtk_frame_new ("Move");
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, TRUE, 0);

  vbox = gtk_vbox_new (FALSE, 3);
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), vbox);

  tmp = g_strdup ("Into Vault \342\206\222");
  window_vault.button_intovault = gtk_button_new_with_label (tmp);
  g_free (tmp);
  gtk_box_pack_start (GTK_BOX (vbox), window_vault.button_intovault, FALSE, TRUE, 0);

  tmp = g_strdup ("\342\206\220 From Vault");
  window_vault.button_fromvault = gtk_button_new_with_label (tmp);
  g_free (tmp);
  gtk_box_pack_start (GTK_BOX (vbox), window_vault.button_fromvault, FALSE, TRUE, 0);


  frame = gtk_frame_new ("In the Vault");
  gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 0);

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_NEVER,
                                  GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window),
                                       GTK_SHADOW_IN);
  gtk_widget_set_size_request (scrolled_window, -1, 210);
  gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 5);
  gtk_container_add (GTK_CONTAINER (frame), scrolled_window);

  window_vault.treeview_vault = create_treeview_drug (FALSE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), window_vault.treeview_vault);


  hbox = gtk_hbutton_box_new ();
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbox), GTK_BUTTONBOX_END);
  gtk_box_set_spacing (GTK_BOX (hbox), 3);
  gtk_box_pack_start (GTK_BOX (vbox_main), hbox, FALSE, TRUE, 0);

  window_vault.button_ok = gtk_button_new_with_mnemonic ("_OK");
  gtk_box_pack_start (GTK_BOX (hbox), window_vault.button_ok, FALSE, TRUE, 0);

  button = gtk_button_new_with_mnemonic ("_Cancel");
  gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, TRUE, 0);
  g_signal_connect_swapped (button, "clicked", 
                            G_CALLBACK (gtk_widget_destroy), window_vault.window);
}

void
create_window_input (const gchar *title,
                     const gchar *message,
                     const gchar *question)
{
  GtkWidget *frame;
  GtkWidget *label;
  GtkWidget *vbox_main, *hbox;
  GtkWidget *button;

  window_input.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window_input.window), title);
  gtk_window_set_type_hint (GTK_WINDOW (window_input.window), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_window_set_transient_for (GTK_WINDOW (window_input.window),
                                GTK_WINDOW (window_main.window));
  gtk_window_set_modal (GTK_WINDOW (window_input.window), TRUE);
  gtk_window_set_resizable (GTK_WINDOW (window_input.window), FALSE);
  g_signal_connect_swapped (window_input.window, "destroy", 
                            G_CALLBACK (gtk_widget_destroy), window_input.window);

  vbox_main = gtk_vbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (vbox_main), 5);
  gtk_container_add (GTK_CONTAINER (window_input.window), vbox_main);

  frame = gtk_frame_new ("Message");
  gtk_box_pack_start (GTK_BOX (vbox_main), frame, FALSE, TRUE, 0);

  hbox = gtk_hbox_new (FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), hbox);

  label = gtk_label_new (message);
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, TRUE, 0);


  frame = gtk_frame_new (NULL);
  gtk_box_pack_start (GTK_BOX (vbox_main), frame, FALSE, TRUE, 0);

  hbox = gtk_hbox_new (FALSE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), hbox);

  label = gtk_label_new (question);
  gtk_misc_set_alignment (GTK_MISC (label), 1.0, 0.5);
  gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

  window_input.spinbutton_value = gtk_spin_button_new_with_range (1.0, 1000000.0, 1.0);
  gtk_spin_button_set_digits (GTK_SPIN_BUTTON (window_input.spinbutton_value), 0);
  gtk_box_pack_start (GTK_BOX (hbox), window_input.spinbutton_value, FALSE, TRUE, 0);

  hbox = gtk_hbutton_box_new ();
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbox), GTK_BUTTONBOX_END);
  gtk_box_set_spacing (GTK_BOX (hbox), 5);
  gtk_box_pack_start (GTK_BOX (vbox_main), hbox, FALSE, TRUE, 0);

  window_input.button_ok = gtk_button_new_with_mnemonic ("_OK");
  gtk_container_add (GTK_CONTAINER (hbox), window_input.button_ok);

  button = gtk_button_new_with_mnemonic ("_Cancel");
  gtk_container_add (GTK_CONTAINER (hbox), button);
  g_signal_connect_swapped (button, "clicked", 
                            G_CALLBACK (gtk_widget_destroy), window_input.window);
}

GtkWidget*
create_places_menu ()
{
  GtkWidget *menu;
  GtkWidget *menuitem;

  menu = gtk_menu_new ();

  menuitem = gtk_menu_item_new_with_label ("Finances...");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
  g_signal_connect (menuitem, "activate",
                    G_CALLBACK (menuitem_places_finances_activate_cb), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label ("Shopping...");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
  g_signal_connect (menuitem, "activate",
                    G_CALLBACK (menuitem_places_shopping_activate_cb), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label ("Hospital...");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
  g_signal_connect (menuitem, "activate",
                    G_CALLBACK (menuitem_places_hospital_activate_cb), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label ("Vault...");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
  g_signal_connect (menuitem, "activate",
                    G_CALLBACK (menuitem_places_vault_activate_cb), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label ("Shipping...");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
  g_signal_connect (menuitem, "activate",
                    G_CALLBACK (menuitem_places_shipping_activate_cb), NULL);
  gtk_widget_show (menuitem);

  return menu;
}

GtkWidget*
create_info_menu ()
{
  GtkWidget *menu;
  GtkWidget *menuitem;

  menu = gtk_menu_new ();

  menuitem = gtk_menu_item_new_with_label ("Vaults...");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
  g_signal_connect (menuitem, "activate",
                    G_CALLBACK (menuitem_info_vaults_activate_cb), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label ("World Drug Prices...");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
  g_signal_connect (menuitem, "activate",
                    G_CALLBACK (menuitem_info_drug_prices_activate_cb), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label ("World Cities...");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
  g_signal_connect (menuitem, "activate",
                    G_CALLBACK (menuitem_info_world_cities_activate_cb), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label ("Shipment Status...");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
  g_signal_connect (menuitem, "activate",
                    G_CALLBACK (menuitem_info_shipment_status_activate_cb), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label ("History...");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
  g_signal_connect (menuitem, "activate",
                    G_CALLBACK (menuitem_info_history_activate_cb), NULL);
  gtk_widget_show (menuitem);

  return menu;
}

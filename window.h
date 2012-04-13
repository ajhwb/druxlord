#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <gtk/gtk.h>

typedef struct
{
  GtkWidget *window;
  GtkWidget *textview_information;
  GtkWidget *treeview_market;
  GtkWidget *treeview_pocket;
  GtkWidget *button_buy;
  GtkWidget *button_sell;
  GtkWidget *button_dump;
  GtkWidget *button_places;
  GtkWidget *button_info;
  GtkWidget *button_stayhere;
  GtkWidget *button_flyaway;
  GtkWidget *button_about;
  GtkWidget *button_docs;
  GtkWidget *button_highscores;
  GtkWidget *button_newgamequit;
  GtkWidget *checkbutton_sound;
  GtkWidget *label_pocket;
  GtkWidget *label_location;
  GtkWidget *label_day;
  GtkWidget *label_rank;
  GtkWidget *label_cash;
  GtkWidget *label_bank;
  GtkWidget *label_debt;
  GtkWidget *progressbar_health;
  GtkWidget *drawingarea_status;
} WindowMain;

typedef struct
{
  GtkWidget *window;
  GtkWidget *radiobutton_depositsome;
  GtkWidget *radiobutton_depositall;
  GtkWidget *radiobutton_depositallbut;
  GtkWidget *radiobutton_withdrawsome;
  GtkWidget *radiobutton_withdrawall;
  GtkWidget *radiobutton_withdrawallbut;
  GtkWidget *spinbutton_amount;
  GtkWidget *button_doit;
  GtkWidget *treeview_loan;
  GtkWidget *label_cash;
  GtkWidget *label_bank;
  GtkWidget *label_debt;
  GtkWidget *button_borrow;
  GtkWidget *button_repay;
  GtkWidget *button_done;
} WindowFinance;

typedef struct
{
  GtkWidget *window;
  GtkWidget *treeview_store;
  GtkWidget *treeview_inventory;
  GtkWidget *button_buy;
  GtkWidget *button_sell;
  GtkWidget *button_done;
  GtkWidget *label_cash;
} WindowShopping;

typedef struct
{
  GtkWidget *window;
  GtkWidget *progressbar_health;
  GtkWidget *scalebutton_health;
  GtkWidget *label_cash;
  GtkWidget *label_cost;
  GtkWidget *button_ok;
} WindowHospital;

typedef struct
{
  GtkWidget *window;
  GtkWidget *treeview_pocket;
  GtkWidget *treeview_vault;
  GtkWidget *button_intovault;
  GtkWidget *button_fromvault;
  GtkWidget *button_ok;
} WindowVault;

typedef struct
{
  GtkWidget *window;
  GtkWidget *spinbutton_value;
  GtkWidget *button_ok;
} WindowInput;

enum
{
  COLUMN_STATUS,
  COLUMN_NAME,
  COLUMN_QTY,
  COLUMN_PRICE
};

enum
{
  COLUMN_LOAN_NAME,
  COLUMN_LOAN_PAY,
  COLUMN_LOAN_RATE,
  COLUMN_LOAN_DAY,
  COLUMN_LOAN_DEBT,
  COLUMN_LOAN_DAYLEFT
};

enum
{
  COLUMN_STORE_NAME,
  COLUMN_STORE_TYPE,
  COLUMN_STORE_PRICE
};

enum
{
  COLUMN_INVENTORY_NAME,
  COLUMN_INVENTORY_TYPE,
  COLUMN_INVENTORY_QTY,
  COLUMN_INVENTORY_SELLFOR
};

enum
{
  COLUMN_VAULT_NAME,
  COLUMN_VAULT_QTY,
  COLUMN_VAULT_PRICE
};

WindowMain window_main;
WindowFinance window_finance;
WindowShopping window_shopping;
WindowHospital window_hospital;
WindowVault window_vault;
WindowInput window_input;

void create_window_main ();
void create_window_finance ();
void create_window_shopping ();
void create_window_hospital ();
void create_window_vault ();
void create_window_input (const gchar *title,
                          const gchar *message,
                          const gchar *question);

void insert_treeview_drug (GtkTreeView *treeview);
void set_label_frame_pocket (gint npocket);
void set_label_location (gint location);
void set_label_day (gint day);
void set_label_rank (gint rank);
void set_label_cash (gint value);
void set_label_bank (gint value);
void set_label_debt (gint value);
GtkWidget* create_places_menu ();
GtkWidget* create_info_menu ();

#endif

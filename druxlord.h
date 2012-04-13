#ifndef __DRUXLORD_H__
#define __DRUXLORD_H__

#include <glib.h>

#define DRUG_NUM   17
#define CITY_NUM   15

typedef enum
{
  DRUG_COCAINE,
  DRUG_CRACK,
  DRUG_ECSTACY,
  DRUG_HASHISH,
  DRUG_HEROIN,
  DRUG_ICE,
  DRUG_KAT,
  DRUG_LSD,
  DRUG_MDA,
  DRUG_MORPHIN,
  DRUG_MUSHROOMS,
  DRUG_OPIUM,
  DRUG_PCP,
  DRUG_PEYOTE,
  DRUG_POT,
  DRUG_SPECIALK,
  DRUG_SPEED
} DrugType;

typedef enum
{
  WEAPON_KNIFE,
  WEAPON_PISTOL,
  WEAPON_SHOTGUN,
  WEAPON_MACHINEGUN,
  WEAPON_FLAMETHROWER,
  WEAPON_DYNAMITE,
  WEAPON_GRENADE,
  WEAPON_ROCKETLAUNCHER,
  WEAPON_AREADISRUPTER
} WeaponType;
  
typedef enum
{
  AMMO_PISTOLBULLET,
  AMMO_SHOTGUNSHELL,
  AMMO_MACHINEGUNBULLET,
  AMMO_GASCANISTER,
  AMMO_ROCKET,
  AMMO_ENERGYGLOBE
} AmmoType;

typedef enum
{
  ARMOR_HEAVYLEATHERCOAT,
  ARMOR_BULLETPROOFVEST
} ArmorType;

typedef enum
{
  ITEM_CANOFNOSCENT
} ItemType;

typedef enum
{
  CITY_AUSTIN,
  CITY_BEIJING,
  CITY_BOSTON,
  CITY_DETROIT,
  CITY_LONDON,
  CITY_LOSANGELES,
  CITY_MIAMI,
  CITY_MOSCOW,
  CITY_NEWYORK,
  CITY_PARIS,
  CITY_SANFRANCISCO,
  CITY_STPETERSBURG,
  CITY_SYDNEY,
  CITY_TORONTO,
  CITY_VANCOUVER
} CityType;

typedef enum
{
  COUNTRY_AUSTRALIA,
  COUNTRY_CANADA,
  COUNTRY_CHINA,
  COUNTRY_FRANCE,
  COUNTRY_UK,
  COUNTRY_USA,
  COUNTRY_RUSSIA
} CountryType;

typedef enum
{
  RANK_WANNABE,
  RANK_SMALLTIME,
  RANK_DEALER,
  RANK_BIGDEALER,
  RANK_DISTRIBUTER,
  RANK_DRUGLORD
} RankType;

typedef struct
{
  gint id;
  gint country;
} City;

typedef struct
{
  gint qty;
  gint price;
  gboolean available;
} Drug;

typedef struct
{
  gint id;
  gint ammo;
  gint destruction;
  gboolean mass_effect;
  gboolean has_ammo;
  gint price;
} Weapon;

typedef struct
{
  gint type;       /* Rank type */
  gulong cash;     /* Minimum cash to achieve this rank */
  gint container;  /* Container type */
  gint capacity;   /* Container capacity */
} Rank;

extern const char * const drug_name[DRUG_NUM];

extern const int drug_price[DRUG_NUM];

extern const char * const city_name[CITY_NUM];

extern const char * const country_name[];

extern const Weapon weapon_info[];

extern const City city_info[CITY_NUM];

extern GSList *city_list;


extern Drug drug_table[DRUG_NUM][CITY_NUM];

gchar* money_string (guint value);
void generate_drug ();

#endif

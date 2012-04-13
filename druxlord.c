#include <glib.h>
#include "druxlord.h"

const char * const drug_name[DRUG_NUM] =
{
  "Cocaine",
  "Crack",
  "Ecstasy",
  "Hashish",
  "Heroin",
  "Ice",
  "Kat",
  "LSD",
  "MDA",
  "Morphine",
  "Mushrooms",
  "Opium",
  "PCP",
  "Peyote",
  "Pot",
  "Special K",
  "Speed"
};

const int drug_price[DRUG_NUM] = 
{
  4000,
  4000,
  3000,
  2000,
  1000,
  1000,
  1000,
  1000,
  1000,
  3000,
  200,
  900,
  900,
  900,
  800,
  600,
  500
};

const char * const city_name[CITY_NUM] =
{
  "Austin",
  "Beijing",
  "Boston",
  "Detroit",
  "London",
  "Los Angeles",
  "Miami",
  "Moscow",
  "New York",
  "Paris",
  "San Francisco",
  "St Petersburg",
  "Sydney",
  "Toronto",
  "Vancouver"
};

const char * const country_name[] =
{
  "Australia",
  "Canada",
  "China",
  "England",
  "France",
  "USA",
  "Russia"
};

const Weapon weapon_info[] =
{
  { WEAPON_KNIFE,           0,                     20, FALSE, FALSE, 100    },
  { WEAPON_PISTOL,          AMMO_PISTOLBULLET,     40, FALSE, TRUE,  500    },
  { WEAPON_SHOTGUN,         AMMO_SHOTGUNSHELL,     50, FALSE, TRUE,  2500   },
  { WEAPON_MACHINEGUN,      AMMO_MACHINEGUNBULLET, 60, TRUE,  TRUE,  4000   },
  { WEAPON_FLAMETHROWER,    AMMO_GASCANISTER,      70, TRUE,  TRUE,  7500   },
  { WEAPON_DYNAMITE,        0,                     35, TRUE,  FALSE, 250    },
  { WEAPON_GRENADE,         0,                     50, TRUE,  FALSE, 500    },
  { WEAPON_ROCKETLAUNCHER,  AMMO_ROCKET,           70, TRUE,  TRUE,  10000  },
  { WEAPON_AREADISRUPTER,   AMMO_ENERGYGLOBE,      99, TRUE,  TRUE,  500000 }
};

const City city_info[CITY_NUM] =
{
  { CITY_AUSTIN,        COUNTRY_USA       },
  { CITY_BEIJING,       COUNTRY_CHINA     },
  { CITY_BOSTON,        COUNTRY_USA       },
  { CITY_DETROIT,       COUNTRY_USA       },
  { CITY_LONDON,        COUNTRY_UK        },
  { CITY_LOSANGELES,    COUNTRY_USA       },
  { CITY_MIAMI,         COUNTRY_USA       },
  { CITY_MOSCOW,        COUNTRY_RUSSIA    },
  { CITY_NEWYORK,       COUNTRY_USA       },
  { CITY_PARIS,         COUNTRY_FRANCE    },
  { CITY_SANFRANCISCO,  COUNTRY_USA       },
  { CITY_STPETERSBURG,  COUNTRY_RUSSIA    },
  { CITY_SYDNEY,        COUNTRY_AUSTRALIA },
  { CITY_TORONTO,       COUNTRY_CANADA    },
  { CITY_VANCOUVER,     COUNTRY_CANADA    }
};

GSList *city_list = NULL;
Drug drug_table[DRUG_NUM][CITY_NUM];

gchar*
money_string (guint value)
{
  gchar *tmp, *ret, *ptr_tmp, *ptr_ret;
  gint comma = 0, i = 0;
  guint tmp_value = value;
  guint len;

  while ((tmp_value /= 1000))
    comma++;

  tmp = g_strdup_printf ("%u", value);
  len = g_utf8_strlen (tmp, -1);
  ret = g_new (gchar, len + comma + 1);

  ptr_tmp = tmp + len;
  ptr_ret = ret + len + comma;

  *ptr_ret-- = *ptr_tmp--;

  while (ptr_tmp >= tmp)
    {
      if (i < 3)
        {
          *ptr_ret-- = *ptr_tmp--;
          i++;
        }
      else
        {
          *ptr_ret-- = ',';
          i = 0;
        }
    }

  g_free (tmp);
  return ret;
}

void
generate_drug ()
{
  GRand *rand;
  gint i, j, divisor;

  rand = g_rand_new ();

  for (i = 0; i < DRUG_NUM; i++)
    for (j = 0; j < CITY_NUM; j++)
      {
        drug_table[i][j].available = g_rand_boolean (rand);
        if (drug_table[i][j].available)
          {
            drug_table[i][j].qty = g_rand_int_range (rand, 0, 10);
            if (drug_table[i][j].qty > 0)
              divisor = drug_table[i][j].qty;
            else
              divisor = g_rand_int_range (rand, 1, 10);
            drug_table[i][j].price = ((double) 10 / divisor) *
                                     g_rand_double_range (rand, 0.1, 1.0) * 
                                     drug_price[i];
          }
      }

  g_rand_free (rand);
}

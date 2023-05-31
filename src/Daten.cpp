#include "Daten.h"
#include <mosquitto.h>

Daten::Daten()
{
    t[T_KiVo_IST ] =-66.0;
    t[T_KiVo_SOLL]= 20.0;
    t[T_KiHi_IST ]=-66.0;
    t[T_KiHi_SOLL]= 20.0;
    t[T_BAD_IST  ]=-66.0;
    t[T_BAD_SOLL ]= 22.0;
    t[T_ELT_IST  ]=-66.0;
    t[T_ELT_SOLL ]= 20.0;
    t[T_UMG      ]=-66.0;
    for (int i = 0; i<=R_ANZAHL; ++i)
        {rZust[i]=RolladenZust::voll_offen;
         rWahl[i]=false;}
}

float Daten::get_t(TEMP_ENUM ort)
{
    return (t[ort]);
}

void Daten::set_t(TEMP_ENUM ort, float wert)
{
    t[ort]=wert;
}

RolladenZust Daten::get_rZust(ROLL_ENUM ort)
{
    return (rZust[ort]);
}

void Daten::set_rZust(ROLL_ENUM ort, RolladenZust wert)
{
    rZust[ort]=wert;
}

bool Daten::get_rWahl(ROLL_ENUM ort)
{
    return (rWahl[ort]);
}

void Daten::set_rWahl(ROLL_ENUM ort, bool wert)
{
    rWahl[ort]=wert;
}
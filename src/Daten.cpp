#include "Daten.h"

Daten::Daten()
{
    for (int i = 0; i<=T_ANZAHL; ++i)
        {t[i]=-66.6;}
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
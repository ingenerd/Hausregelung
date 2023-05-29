#ifndef SRC_DATEN_H
#define SRC_DATEN_H

// Alle Temperaturen kriegen einen Namen und werden unter der Enum-Nummer des Namens in einem Array gespeichert
// T_ANZAHL wird gebraucht zum Erstellen des Arrays (Größe) und muss ergo der letzte Eintrag der Enum sein
// Eine Enum Class kann nicht so einfach in einen int umgemünzt werden - das ginge mit static_cast und ist mir zu umständlich
enum TEMP_ENUM {T_KiVo_IST, T_KiVo_SOLL, 
                T_KiHi_IST, T_KiHi_SOLL,
                T_BAD_IST , T_BAD_SOLL ,
                T_ELT_IST , T_ELT_SOLL ,
                T_UMG, 
                T_ANZAHL};

// Analog für die Rolläden ...
enum ROLL_ENUM {R_KiVo1, R_KiVo2,
                R_KiHi1, R_KiHi2,
                R_Bad  , R_Elt  ,
                R_ANZAHL};

//Rolladen-Zustände
enum class RolladenZust {
  voll_offen, voll_geschlossen, halb_offen, lichtspalte  
};

class Daten
{
    public:
        Daten();
        float get_t(TEMP_ENUM ort);
        void  set_t(TEMP_ENUM ort, float wert);

        RolladenZust get_rZust(ROLL_ENUM ort);
        void  set_rZust(ROLL_ENUM ort, RolladenZust wert);

        bool get_rWahl(ROLL_ENUM ort);
        void  set_rWahl(ROLL_ENUM ort, bool wert);
    
    private:
        //Temperaturen
        float t[T_ANZAHL];
        //Rolläden
        RolladenZust rZust[R_ANZAHL];
        bool rWahl[R_ANZAHL];


};

#endif /* SRC_DATEN_H_ */
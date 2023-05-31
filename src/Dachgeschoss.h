#ifndef SRC_DACHGESCHOSS_H_
#define SRC_DACHGESCHOSS_H_

#include <ctime>
#include "definitions.h"

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/window.h>
//#include <gtkmm/eventbox.h>

#include <memory>

#include "Daten.h"
#include "DG_Anzeige.h"
#include "RolladenMenu.h"
#include "tSollMenu.h"

class Dachgeschoss : public Gtk::Grid
{

public:
  Dachgeschoss(std::shared_ptr<Daten>& data, struct mosquitto *mosq);
  
  void RolladenFahren();

  Daten& get_allData();

  void tSoll_menu(TEMP_ENUM wo); //tSollmenü einblenden (Muss public sein, da die DG_Anzeige darauf zugreift)
  void set_tSoll(TEMP_ENUM wo, float wert);

private:
  sigc::connection uhrTick;
  bool uhrAktualisieren();
  char datum_str[14]; //alter Typ, um mit den ctime-Funktionen zu arbeiten
  char uhr_str[9];    //alter Typ, um mit den ctime-Funktionen zu arbeiten

  Gtk::Label datum, uhrzeit;

  //Signal handlers:
  void next_modus(); //Anzeige durchtoggeln rechts
  void prev_modus(); //Anzeige durchtoggeln links

  void rolladen_menu(); //Rolladenmenü einblenden
  bool rolladen_menu_hide(GdkEventFocus* event); //Rolladenmenü ausblenden

  bool tSoll_menu_hide(GdkEventFocus* event); //tSollmenü ausblenden

  //Bildschirmaufteilung:
  Gtk::Grid grid_haupt_teilung;
  Gtk::Grid grid_links;
  Gtk::Grid grid_rechts;
  Gtk::Grid grid_anzeige_wechsel; //unter Anzeige

  //eigene Fenster
  //Menüführung Rolladen
  RolladenMenu window_rolladen;
  //Sollwerte für Temperaturen
  tSollMenu window_tSoll;

  //Zugriff auf lokales Datenobjekt
  std::shared_ptr<Daten> allData;

  //Für MQTT Kommunikation
  struct mosquitto *mosq;

  //graphische Anzeige des Grundrisses mit Daten
  //Gtk::EventBox eventbox; // war zu Testzwecken drin... kann am Ende wohl weg
  DG_Anzeige anzeige;

  //buttons unter Anzeige zum durchtoggeln
  Gtk::Button button_anzeige_wechsel_links;
  Gtk::Button button_anzeige_wechsel_rechts;

  //button für Rolladenmenü-Fenster
  Gtk::Button button_rolladen;
};

#endif /* SRC_DACHGESCHOSS_H_ */

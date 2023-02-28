/*
 * Dachgeschoss.h
 *
 *  Created on: Dec 13, 2022
 *      Author: bejo
 */

#ifndef SRC_DACHGESCHOSS_H_
#define SRC_DACHGESCHOSS_H_

#include "definitions.h"

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/window.h>
//#include <gtkmm/eventbox.h>

#include "Anzeige.h"
#include "RolladenMenu.h"

// die mosquitto handler kriege ich nicht in eine class oder einen namespace rein
// da die *_set-Methoden (z.B.: mosquitto_message_callback_set) der mosquitto API (*void) als Returnierwert verlangen, wüsste ich nicht wie ich auf eine Funktion innerhaln eines namepsaces casten kann...
// Deklaration hier - Definition im zugehörigen *.cpp-file
void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message);

class Dachgeschoss : public Gtk::Window
{

public:
  Dachgeschoss();
  virtual ~Dachgeschoss();
  void set_t(float value, ZimmerTemp identifier);
  Visualisierung get_modus();
  void RolladenFahren();

private:
  //Signal handlers:
  void on_button_clicked(); //testzwecke
  void next_modus(); //Anzeige durchtoggeln rechts
  void prev_modus(); //Anzeige durchtoggeln links
  void rolladen_menu(); //Rolladenmenü einblenden
  bool rolladen_menu_hide(GdkEventFocus* event); //Rolladenmenü ausblenden
  bool on_anzeige_clicked(GdkEventButton*); //Reaktion auf Klick in Anzeige

  //Bildschirmaufteilung:
  Gtk::Grid grid_haupt_teilung; //Vertikal:     0-530 + 530-800
  Gtk::Grid grid_links;         //Horizontal:   0-400 + 400-480
  Gtk::Grid grid_rechts;        //Horizontal:   Platz für buttons
  Gtk::Grid grid_anzeige_wechsel; //unter Anzeige

  //Menüführung Rolladen in eigenem Fenster
  RolladenMenu window_rolladen;

  // graphische Anzeige des Grundrisses mit Daten
  //Gtk::EventBox eventbox; // war zu Testzwecken drin... kann am Ende wohl weg
  Anzeige anzeige;

  //buttons unter Anzeige zum durchtoggeln
  Gtk::Button button_anzeige_wechsel_links;
  Gtk::Button button_anzeige_wechsel_rechts;

  //button für Rolladenmenü-Fenster
  Gtk::Button button_rolladen;
  
  //Testzwecke
  Gtk::Button m_button;
  Gtk::Label m_label;

  // eine Funktion, die von GTK immer wieder getriggert wird
  // zum Beispiel um die aktuellsten Wetterdaten abzufragen
  bool again_and_again();
  // mit zugehöriger sigc::connection, um später aufräumen zu können
  sigc::connection dauerTrigger;

  //Mosquitto-Instanz (reine C-Bibliothek) zur Kommunikation über mqtt
  struct mosquitto *mosq;
};

#endif /* SRC_DACHGESCHOSS_H_ */

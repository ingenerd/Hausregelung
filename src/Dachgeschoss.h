/*
 * Dachgeschoss.h
 *
 *  Created on: Dec 13, 2022
 *      Author: bejo
 */

#ifndef SRC_DACHGESCHOSS_H_
#define SRC_DACHGESCHOSS_H_

// für timeout gegebenenfalls besseren include finden
#include <gtkmm.h>

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/window.h>

#include "Anzeige.h"

// die mosquitto handler kriege ich nicht in eine class oder einen namespace rein
// da die *_set-Methoden (z.B.: mosquitto_message_callback_set) der mosquitto API (*void) als Returnierwert verlangen, wüsste ich nicht wie ich auf eine Funktion innerhaln eines namepsaces casten kann...
// Deklaration hier - Definition im zugehörigen *.cpp-file
void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message);

class Dachgeschoss : public Gtk::Window
{

public:
  Dachgeschoss();
  virtual ~Dachgeschoss();
  void set_t_Elt_IST(float);

private:
  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Grid grid_anordnung;
  Gtk::Grid grid_buttons;

  // graphische Anzeige des Grundrisses mit Daten
  Anzeige anzeige;
  
  Gtk::Button m_button;
  Gtk::Label m_label;

  // eine Funktion, die von GTK immer wieder getriggert wird
  bool again_and_again();
  // mit zugehöriger sigc::connection, um später aufräumen zu können
  sigc::connection dauerTrigger;
  struct mosquitto *mosq;
};

#endif /* SRC_DACHGESCHOSS_H_ */

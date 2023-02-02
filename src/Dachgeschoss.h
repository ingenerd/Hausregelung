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

class Dachgeschoss : public Gtk::Window
{

public:
  Dachgeschoss();
  virtual ~Dachgeschoss();
  //Cairo::RefPtr<Cairo::Context>& getContext() {return myContext;};
  void set_t_Elt_IST(float);

private:
  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Grid grid_anordnung;
  Gtk::Grid grid_buttons;

  Anzeige anzeige;
  //Cairo::RefPtr<Cairo::Context> myContext;
  Gtk::Button m_button;
  Gtk::Label m_label;

  bool again_and_again();
  struct mosquitto *mosq;
};

#endif /* SRC_DACHGESCHOSS_H_ */

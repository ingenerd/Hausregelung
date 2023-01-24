/*
 * Dachgeschoss.h
 *
 *  Created on: Dec 13, 2022
 *      Author: bejo
 */

#ifndef SRC_DACHGESCHOSS_H_
#define SRC_DACHGESCHOSS_H_

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

private:
  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Grid grid_anordnung;
  Gtk::Grid grid_buttons;

  Anzeige anzeige;
  Gtk::Button m_button;
  Gtk::Label m_label;

  int pos_x_text_Bad;
  int pos_y_text_Bad;
};

#endif /* SRC_DACHGESCHOSS_H_ */

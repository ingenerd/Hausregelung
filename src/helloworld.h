/*
 * helloworld.h
 *
 *  Created on: Dec 13, 2022
 *      Author: bejo
 */

#ifndef SRC_HELLOWORLD_H_
#define SRC_HELLOWORLD_H_

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/window.h>

class HelloWorld : public Gtk::Window
{

public:
  HelloWorld();
  virtual ~HelloWorld();

protected:
  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Grid m_grid;
  Gtk::Button m_button;
  Gtk::Label m_label;
};

#endif /* SRC_HELLOWORLD_H_ */

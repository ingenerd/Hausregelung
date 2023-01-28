/*
 * Dachgeschoss.cpp
 *
 *  Created on: Dec 13, 2022
 *      Author: bejo
 */

#include "Dachgeschoss.h"
#include <iostream>
#include <glibmm.h>
#include <giomm.h>

#include <gtkmm/cssprovider.h>

Dachgeschoss::Dachgeschoss()
{
  set_default_size(800, 480);
  //fullscreen();
  set_size_request(800,480);
  set_decorated(false);
  set_resizable(false);  
  set_position(Gtk::WIN_POS_CENTER);
  //set_border_width(25);

  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
  //std::cout << "Hi " << (Gio::File::create_for_path("../style/styles.css"))->get_path();
  //css_provider->load_from_path((Gio::File::create_for_path("../style/styles.css"))->get_path());
  //css_provider->load_from_path("../style/styles.css");
  css_provider->load_from_path("/home/bejo/git/Hausregelung/style/styles.css");

  m_button = Gtk::Button("Rolladen");
  m_label = Gtk::Label("Toll");

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::on_button_clicked));
  //m_button.high
  //m_grid.set_row_spacing(1);
  //m_grid.set_column_spacing(2);
  //m_grid.set_column_homogeneous(true);
  //m_grid.set_row_homogeneous(true);

  //m_grid.attach(m_button, 0, 0);
  //m_grid.attach(m_label, 0, 1);

  grid_anordnung.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  grid_buttons.set_orientation(Gtk::ORIENTATION_VERTICAL);

  grid_buttons.add(m_button);
  grid_buttons.add(m_label);

  grid_anordnung.add(anzeige);
  grid_anordnung.add(grid_buttons);

  add(grid_anordnung);

  
  /*css_provider->load_from_data(
    "button {background-image: image(cyan);}\
     button:hover {background-image: image(green);}\
     button:active {background-image: image(brown);}\
     label {background-image: none;}\
	 window.background {background-image: url(\"style/test.jpeg\") }");
  */
  m_button.get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  m_label.get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  // The final step is to display this newly created widget...
  m_button.show();
  show_all_children();

  //infinite loop every 1000 milliseconds
  sigc::connection conn = Glib::signal_timeout().connect(sigc::mem_fun((*this),&Dachgeschoss::again_and_again), 1000, Glib::PRIORITY_DEFAULT);
}  

Dachgeschoss::~Dachgeschoss()
{
}

bool Dachgeschoss::again_and_again()
{
  std::cout << "Tick Tock" << std::endl;
  return true;
}

void Dachgeschoss::on_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}




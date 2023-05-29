/*
 * Dachgeschoss.cpp
 *
 *  Created on: Dec 13, 2022
 *      Author: bejo
 */

#include "Dachgeschoss.h"
#include "definitions.h"
#include <iostream>
#include <glibmm.h>
#include <giomm.h>
#include <gtkmm/cssprovider.h>
#include <string>
#include <chrono>

#include <mosquitto.h>

Dachgeschoss::Dachgeschoss(std::shared_ptr<Daten>& data) : window_rolladen(*this), window_tSoll(*this), allData(data), anzeige(data, *this)
{
  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
  //std::cout << "Hi " << (Gio::File::create_for_path("../style/styles.css"))->get_path();
  //css_provider->load_from_path((Gio::File::create_for_path("../style/styles.css"))->get_path());
  //css_provider->load_from_path("../style/styles.css");
  css_provider->load_from_path("/home/bejo/git/Hausregelung/style/styles.css");

  m_button = Gtk::Button("Rolladen");
  m_label = Gtk::Label("Toll");
  button_anzeige_wechsel_links = Gtk::Button("<---");
  button_anzeige_wechsel_links.set_size_request(-1,30);
  button_anzeige_wechsel_rechts = Gtk::Button("--->");
  button_anzeige_wechsel_rechts.set_size_request(-1,30);
  button_rolladen = Gtk::Button("Rolläden");
  button_rolladen.set_size_request(170,50);

  grid_haupt_teilung.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  grid_links.set_orientation(Gtk::ORIENTATION_VERTICAL);
  grid_rechts.set_orientation(Gtk::ORIENTATION_VERTICAL);
  grid_anzeige_wechsel.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

  grid_haupt_teilung.add(grid_links);
  grid_haupt_teilung.add(grid_rechts);

  grid_links.add(anzeige);
  grid_links.add(grid_anzeige_wechsel);

  grid_anzeige_wechsel.add(button_anzeige_wechsel_links);
  grid_anzeige_wechsel.add(button_anzeige_wechsel_rechts);
  grid_anzeige_wechsel.set_column_spacing(150);
  grid_anzeige_wechsel.set_column_homogeneous(false);
  grid_anzeige_wechsel.set_halign(Gtk::ALIGN_CENTER);
  grid_anzeige_wechsel.set_margin_top(SPACER);
  
  grid_rechts.add(m_button);
  grid_rechts.add(m_label);
  grid_rechts.add(button_rolladen);
  
  add(grid_haupt_teilung);

  //eventbox.set_events(Gdk::BUTTON_PRESS_MASK);
  //eventbox.signal_button_press_event().connect(sigc::mem_fun(*this,&Dachgeschoss::test));

  //anzeige.add_events(Gdk::BUTTON_PRESS_MASK);
  //anzeige.signal_button_press_event().connect(sigc::mem_fun(*this,&Dachgeschoss::on_anzeige_clicked));
  
  m_button.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::next_modus));
  button_anzeige_wechsel_links.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::prev_modus));
  button_anzeige_wechsel_rechts.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::next_modus));
  button_rolladen.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::rolladen_menu));
  window_rolladen.signal_focus_out_event().connect(sigc::mem_fun(*this,&Dachgeschoss::rolladen_menu_hide));
  window_tSoll.signal_focus_out_event().connect(sigc::mem_fun(*this,&Dachgeschoss::tSoll_menu_hide));

  //m_EventBox.set_events(Gdk::BUTTON_PRESS_MASK);
  //EventBox.signal_button_press_event().connect(sigc::mem_fun(*this, &ExampleWindow::on_eventbox_button_press) );
  

  
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

  show_all_children();
}  

Daten& Dachgeschoss::get_allData()
{
  return *allData.get();
}

void Dachgeschoss::on_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}

void Dachgeschoss::next_modus()
{
  if (anzeige.get_modus() == Visualisierung::Grundriss) {anzeige.set_modus(Visualisierung::Schema)   ;}
  if (anzeige.get_modus() == Visualisierung::Schema   ) {anzeige.set_modus(Visualisierung::Wetter)   ;}
  if (anzeige.get_modus() == Visualisierung::Wetter   ) {anzeige.set_modus(Visualisierung::Grundriss);}
  queue_draw();
}

void Dachgeschoss::prev_modus()
{
  if (anzeige.get_modus() == Visualisierung::Grundriss) {anzeige.set_modus(Visualisierung::Wetter)   ;}
  if (anzeige.get_modus() == Visualisierung::Schema   ) {anzeige.set_modus(Visualisierung::Grundriss);}
  if (anzeige.get_modus() == Visualisierung::Wetter   ) {anzeige.set_modus(Visualisierung::Schema)   ;}
  queue_draw();
}

void Dachgeschoss::rolladen_menu()
{
  window_rolladen.show();
}

void Dachgeschoss::tSoll_menu(TEMP_ENUM wo)
{
  window_tSoll.set_ort(wo);
  window_tSoll.show();
}

void Dachgeschoss::set_tSoll(float wert)
{
  std::cout << "SOLLWERT: " << wert << std::endl;
}

//Dieser Handler für Verlassen des Fensters muss die Form erfüllen: return bool - parameter GdKeventFucos* 
bool Dachgeschoss::rolladen_menu_hide(GdkEventFocus* event)
{
  window_rolladen.hide();
  return true;
}

//Dieser Handler für Verlassen des Fensters muss die Form erfüllen: return bool - parameter GdKeventFucos* 
bool Dachgeschoss::tSoll_menu_hide(GdkEventFocus* event)
{
  window_tSoll.hide();
  return true;
}


void Dachgeschoss::RolladenFahren()
{
  std::cout << "upsi!" << std::endl;
}


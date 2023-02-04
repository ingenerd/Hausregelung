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

#include <mosquitto.h>

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
  //m_button.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::on_button_clicked));
  m_button.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::next_modus));
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
  
  //für immer wieder kehrende Aufgaben muss eine sigc::connection definiert werden
  //war vormals drin, da hierin die mosquitto-Abfragen mit "mosquitto_loop" durchgeführt wurden
  //mosquitto_loop_start ist da wesentlich einfacher 
  dauerTrigger = Glib::signal_timeout().connect(sigc::mem_fun((*this),&Dachgeschoss::again_and_again), 2000, Glib::PRIORITY_DEFAULT);
  
  mosq = mosquitto_new(NULL, true, this);
  mosquitto_message_callback_set(mosq, message_callback);
  mosquitto_connect(mosq, "localhost", 1883, 60);
  mosquitto_subscribe(mosq, NULL, "Sensoren/T/+", 0);
  mosquitto_loop_start(mosq);
}  

Dachgeschoss::~Dachgeschoss()
{
  dauerTrigger.disconnect();
  mosquitto_unsubscribe(mosq, NULL, "Sensoren/T/+");
  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
  bool match = 0;
	std::string payL((char*)message->payload);
  std::string top((char*)message->topic);
  
	std::cout << "Got message " << payL << " for topic " << top << std::endl;

	mosquitto_topic_matches_sub("Sensoren/T/+", message->topic, &match);
  if (match) {
    if (top == "Sensoren/T/Elt") {
      try { static_cast<Dachgeschoss *>(obj)->set_t(std::stof(payL),ZimmerTemp::Elt_IST); }
      catch (...) { std::cout << "Geht nicht!" << std::endl; }
    }
    if (top == "Sensoren/T/Bad") {
      try { static_cast<Dachgeschoss *>(obj)->set_t(std::stof(payL),ZimmerTemp::Bad_IST); }
      catch (...) { std::cout << "Geht nicht!" << std::endl; }
    }
    if (top == "Sensoren/T/KiVo") {
      try { static_cast<Dachgeschoss *>(obj)->set_t(std::stof(payL),ZimmerTemp::KiVo_IST); }
      catch (...) { std::cout << "Geht nicht!" << std::endl; }
    }
    if (top == "Sensoren/T/KiHi") {
      try { static_cast<Dachgeschoss *>(obj)->set_t(std::stof(payL),ZimmerTemp::KiHi_IST); }
      catch (...) { std::cout << "Geht nicht!" << std::endl; }
    }
  }
  static_cast<Dachgeschoss *>(obj)->queue_draw();
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

Visualisierung Dachgeschoss::get_modus()
{
  return (anzeige.get_modus());
}

void Dachgeschoss::next_modus()
{
  Visualisierung akt = get_modus();
  if (akt == Visualisierung::Grundriss) {anzeige.set_modus(Visualisierung::Schema);}
  if (akt == Visualisierung::Schema) {anzeige.set_modus(Visualisierung::Wetter);}
  if (akt == Visualisierung::Wetter) {anzeige.set_modus(Visualisierung::Grundriss);}
}
  
//void prev_modus();

void Dachgeschoss::set_t(float value, ZimmerTemp identifier)
{
  anzeige.set_t(value, identifier);
  show_all_children();
}




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

Dachgeschoss::Dachgeschoss():window_rolladen(*this)
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
  button_anzeige_wechsel_links = Gtk::Button("<---");
  button_anzeige_wechsel_rechts = Gtk::Button("--->");
  button_rolladen = Gtk::Button("Rolladen Steuerung");

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  //m_button.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::on_button_clicked));
  
  //m_button.high
  //m_grid.set_row_spacing(1);
  //m_grid.set_column_spacing(2);
  //m_grid.set_column_homogeneous(true);
  //m_grid.set_row_homogeneous(true);

  //m_grid.attach(m_button, 0, 0);
  //m_grid.attach(m_label, 0, 1);
  //eventbox.add(anzeige);
  //grid_anordnung.add(eventbox);

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
  //grid_anzeige_wechsel.set_row_homogeneous(true);
  grid_anzeige_wechsel.set_row_spacing(20);
  grid_anzeige_wechsel.set_halign(Gtk::ALIGN_CENTER);
  //grid_anzeige_wechsel.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  grid_anzeige_wechsel.set_margin_top(23); // set_valign(Gtk::ALIGN_CENTER);


  grid_rechts.add(m_button);
  grid_rechts.add(m_label);
  grid_rechts.add(button_rolladen);
  
  add(grid_haupt_teilung);

  //eventbox.set_events(Gdk::BUTTON_PRESS_MASK);
  //eventbox.signal_button_press_event().connect(sigc::mem_fun(*this,&Dachgeschoss::test));

  //anzeige.add_events(Gdk::BUTTON_PRESS_MASK);
  anzeige.signal_button_press_event().connect(sigc::mem_fun(*this,&Dachgeschoss::on_anzeige_clicked));
  
  m_button.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::next_modus));
  button_anzeige_wechsel_links.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::prev_modus));
  button_anzeige_wechsel_rechts.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::next_modus));
  button_rolladen.signal_clicked().connect(sigc::mem_fun(*this,&Dachgeschoss::rolladen_menu));
  window_rolladen.signal_focus_out_event().connect(sigc::mem_fun(*this,&Dachgeschoss::rolladen_menu_hide));

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

  // The final step is to display this newly created widgets...
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

void log_light(std::string text)
{
  auto now = std::chrono::system_clock::now().time_since_epoch();
  long millis = static_cast<long>(std::chrono::duration_cast<std::chrono::milliseconds>(now).count());
  long seccis = millis/1000;
  millis = millis%1000;
  std::cerr << seccis << "." << millis << ": " << text << std::endl; 
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
      catch (...) { log_light("MQTT Wert unplausibel für T_IST_Elt!"); }
    }
    if (top == "Sensoren/T/Bad") {
      try { static_cast<Dachgeschoss *>(obj)->set_t(std::stof(payL),ZimmerTemp::Bad_IST); }
      catch (...) { log_light("MQTT Wert unplausibel für T_IST_Bad!"); }
    }
    if (top == "Sensoren/T/KiVo") {
      try { static_cast<Dachgeschoss *>(obj)->set_t(std::stof(payL),ZimmerTemp::KiVo_IST); }
      catch (...) { log_light("MQTT Wert unplausibel für T_IST_KiVo!"); }
    }
    if (top == "Sensoren/T/KiHi") {
      try { static_cast<Dachgeschoss *>(obj)->set_t(std::stof(payL),ZimmerTemp::KiHi_IST); }
      catch (...) { log_light("MQTT Wert unplausibel für T_IST_KiHi!!"); }
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
  queue_draw();
}

void Dachgeschoss::prev_modus()
{
  Visualisierung akt = get_modus();
  if (akt == Visualisierung::Grundriss) {anzeige.set_modus(Visualisierung::Wetter);}
  if (akt == Visualisierung::Schema) {anzeige.set_modus(Visualisierung::Grundriss);}
  if (akt == Visualisierung::Wetter) {anzeige.set_modus(Visualisierung::Schema);}
  queue_draw();
}

bool Dachgeschoss::on_anzeige_clicked(GdkEventButton* event)
{
  std::cout << "X: " << event->x << " - " << "Y: " << event->y << std::endl;

  if (event->x >= anzeige.get_pos('x', ZimmerRolladen::Bad_Roll) &&
      event->x <= anzeige.get_pos('x', ZimmerRolladen::Bad_Roll) + anzeige.get_RollBoxBreite() &&
      event->y >= anzeige.get_pos('y', ZimmerRolladen::Bad_Roll) &&
      event->y <= anzeige.get_pos('y', ZimmerRolladen::Bad_Roll) + anzeige.get_RollBoxBreite())
        {anzeige.toggle_r_auswahl(ZimmerRolladen::Bad_Roll);}
  
  if (event->x >= anzeige.get_pos('x', ZimmerRolladen::KiVo1_Roll) &&
      event->x <= anzeige.get_pos('x', ZimmerRolladen::KiVo1_Roll) + anzeige.get_RollBoxBreite() &&
      event->y >= anzeige.get_pos('y', ZimmerRolladen::KiVo1_Roll) &&
      event->y <= anzeige.get_pos('y', ZimmerRolladen::KiVo1_Roll) + anzeige.get_RollBoxBreite())
        {anzeige.toggle_r_auswahl(ZimmerRolladen::KiVo1_Roll);}
  
  if (event->x >= anzeige.get_pos('x', ZimmerRolladen::KiVo2_Roll) &&
      event->x <= anzeige.get_pos('x', ZimmerRolladen::KiVo2_Roll) + anzeige.get_RollBoxBreite() &&
      event->y >= anzeige.get_pos('y', ZimmerRolladen::KiVo2_Roll) &&
      event->y <= anzeige.get_pos('y', ZimmerRolladen::KiVo2_Roll) + anzeige.get_RollBoxBreite())
        {anzeige.toggle_r_auswahl(ZimmerRolladen::KiVo2_Roll);}
  
  if (event->x >= anzeige.get_pos('x', ZimmerRolladen::KiHi1_Roll) &&
      event->x <= anzeige.get_pos('x', ZimmerRolladen::KiHi1_Roll) + anzeige.get_RollBoxBreite() &&
      event->y >= anzeige.get_pos('y', ZimmerRolladen::KiHi1_Roll) &&
      event->y <= anzeige.get_pos('y', ZimmerRolladen::KiHi1_Roll) + anzeige.get_RollBoxBreite())
        {anzeige.toggle_r_auswahl(ZimmerRolladen::KiHi1_Roll);}
  
  if (event->x >= anzeige.get_pos('x', ZimmerRolladen::KiHi2_Roll) &&
      event->x <= anzeige.get_pos('x', ZimmerRolladen::KiHi2_Roll) + anzeige.get_RollBoxBreite() &&
      event->y >= anzeige.get_pos('y', ZimmerRolladen::KiHi2_Roll) &&
      event->y <= anzeige.get_pos('y', ZimmerRolladen::KiHi2_Roll) + anzeige.get_RollBoxBreite())
        {anzeige.toggle_r_auswahl(ZimmerRolladen::KiHi2_Roll);}
  
  if (event->x >= anzeige.get_pos('x', ZimmerRolladen::Elt_Roll) &&
      event->x <= anzeige.get_pos('x', ZimmerRolladen::Elt_Roll) + anzeige.get_RollBoxBreite() &&
      event->y >= anzeige.get_pos('y', ZimmerRolladen::Elt_Roll) &&
      event->y <= anzeige.get_pos('y', ZimmerRolladen::Elt_Roll) + anzeige.get_RollBoxBreite())
        {anzeige.toggle_r_auswahl(ZimmerRolladen::Elt_Roll);}
  
  queue_draw();

  return true; //es scheint egal zu sein, was returniert wird... dieser Handler darf kein void sein - muss bool sein zum compilieren, aber verhält sich wie void...
}

void Dachgeschoss::set_t(float value, ZimmerTemp identifier)
{
  anzeige.set_t(value, identifier);
}

void Dachgeschoss::rolladen_menu()
{
  window_rolladen.show();
}

//Dieser Handler für Verlassen des Fensters muss die Form erfüllen: return bool - parameter GdKeventFucos* 
bool Dachgeschoss::rolladen_menu_hide(GdkEventFocus* event)
{
  window_rolladen.hide();
  return true;
}
void Dachgeschoss::RolladenFahren()
{
  set_decorated(true);
}


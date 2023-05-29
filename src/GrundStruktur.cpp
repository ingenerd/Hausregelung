#include "GrundStruktur.h"
#include "definitions.h"

#include <iostream>
#include <chrono>

#include <glibmm.h>
#include <giomm.h>

GrundStruktur::GrundStruktur(std::initializer_list<Gtk::Widget* > il)
    : Mitte(il) //die übergebene initializer List wird hier in die Member Variable Mitte kopiert
{
    /*auto t1 = new Gtk::Button("a1");
    auto t2 = new Gtk::Button("a2");
    auto t3 = new Gtk::Button("a3");
    Mitte.push_back(t1);
    Mitte.push_back(t2);
    Mitte.push_back(t3);*/
    
    /*
    for (auto itr = il.begin(); itr != il.end(); ++itr) {
      Mitte.push_back(*itr);
    }*/
    akt_it=Mitte.begin();
    
    //Einstellungen zur Fenstervisualisierung (Größe, keinen oberen Rahmen usw.)
    //Mit GTK kann eine feste Fenstergröße nicht einfach aufgesetzt werden
    //Die Idee von GTK ist offenbar, dass ein Fenster seine Größe verändern kann
    //GTK hat gefühlt tausend Ansätze, um Größenänderungen von Fenstern auf Widgets darin umzusetzen
    //Für ein Touchscrenn ist das ein Desaster - Gtk kommt halt aus einer früheren Zeit...
    //Gtk::Fixed tut es nicht...
    //Irgendwie biege ich die Widgetanordnung so um, dass es passt...
    //Lesson one learnt: Gtk 3.0 ist für Touchscreens ein denkbar schlechter Ansatz!

    set_default_size(BREITE, HOEHE); //Versuche des Festsetzens der Fenstergröße
    set_size_request(BREITE, HOEHE); //Das Hauptfenster kann leider größer werden...
    
    set_decorated(false); //Keine obere Titelzeile
    set_resizable(false); //Keine aktive Fenstergrößenanpassung durch Nutzer (Aber Widgets können die Größe erhöhen...)
    set_position(Gtk::WIN_POS_CENTER); //Darstellen in der Mitte des Displays
    set_border_width(RAND); //Einstellen eines Randes, damit das Display hinter der überlappenden Einhausung voll nutzbar ist...

    button_mitte_wechsel_links = Gtk::Button("<");
    button_mitte_wechsel_links.set_size_request(TOGGLEBREITE,HOEHE-RAND-RAND);
    button_mitte_wechsel_rechts = Gtk::Button(">");
    button_mitte_wechsel_rechts.set_size_request(TOGGLEBREITE,HOEHE-RAND-RAND);
    spacer_links = Gtk::Label("");
    spacer_links.set_size_request(SPACER);
    spacer_rechts = Gtk::Label("");
    spacer_rechts.set_size_request(SPACER);

    grid_haupt_teilung.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

    grid_haupt_teilung.attach(button_mitte_wechsel_links,  0, 0);
    grid_haupt_teilung.attach(spacer_links,                1, 0);
    grid_haupt_teilung.attach(**akt_it,                    2, 0);
    grid_haupt_teilung.attach(spacer_rechts,               3, 0);
    grid_haupt_teilung.attach(button_mitte_wechsel_rechts, 4, 0);

    add(grid_haupt_teilung);

    button_mitte_wechsel_links.signal_clicked().connect(sigc::mem_fun(*this,&GrundStruktur::links_modus));
    button_mitte_wechsel_rechts.signal_clicked().connect(sigc::mem_fun(*this,&GrundStruktur::rechts_modus));

    show_all_children();
    
    //für immer wieder kehrende Aufgaben muss eine sigc::connection definiert werden
    //war vormals drin, da hierin die mosquitto-Abfragen mit "mosquitto_loop" durchgeführt wurden
    //mosquitto_loop_start ist da wesentlich einfacher 
    dauerTrigger = Glib::signal_timeout().connect(sigc::mem_fun((*this),&GrundStruktur::again_and_again), 2000, Glib::PRIORITY_DEFAULT);

}  

GrundStruktur::~GrundStruktur()
{
    dauerTrigger.disconnect();
}

// Anstoßen der queue_draw()-Methode des aktuell angezeigten Widgets
void GrundStruktur::draw()
{
  (*akt_it)->queue_draw();
}

bool GrundStruktur::again_and_again()
{
  std::cout << "Tick Tock" << std::endl;
  return true;
}

void GrundStruktur::links_modus()
{
  std::cout << "Links!" << std::endl;
  grid_haupt_teilung.remove_column(2);
  grid_haupt_teilung.insert_next_to(spacer_links, Gtk::POS_RIGHT);
  if (akt_it == Mitte.begin()) {
    akt_it = Mitte.end()-1; }
  else {
    akt_it--; }
  grid_haupt_teilung.attach(**akt_it,2, 0);

  show_all_children();
  queue_draw();
}

void GrundStruktur::rechts_modus()
{
  std::cout << "Rechts!" << std::endl;
  grid_haupt_teilung.remove_column(2);
  grid_haupt_teilung.insert_next_to(spacer_links, Gtk::POS_RIGHT);
  if (akt_it == Mitte.end()-1) {
    akt_it = Mitte.begin(); }
  else {
    akt_it++; }
  grid_haupt_teilung.attach(**akt_it,2, 0);

  show_all_children();
  queue_draw();
}
#ifndef SRC_ROLLADENMENU_H_
#define SRC_ROLLADENMENU_H_

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>

//RolladenMenu kriegt eine Reference zu Dachgeschoss
//#include "Dachgeschoss.h" funktioniert nicht, da darin RolladenMenu inkludiert ist
//Dann gäbe es eine Art Zirkel Inkludierung, die mein Compiler nicht auseinander kriegt...
//Deshalb muss eine "forward declaration" her:
class Dachgeschoss;

class RolladenMenu : public Gtk::Window
{
  public:
    //RolladenMenu();
    RolladenMenu(Dachgeschoss&);

  private:
    //Referenz zur Mutterebene Dachgeschoss, damit dort eine Änderung der Rolläden ausgeführt werden kann
    Dachgeschoss& hauptEbene;

    Gtk::Button button_ausfuehren;
    Gtk::Label test;
    Gtk::Grid grid_haupt_teilung; 
    Gtk::Grid grid_links;
    Gtk::Grid grid_mitte;
    Gtk::Grid grid_rechts;
};

#endif /* SRC_ROLLADENMENU_H_ */
#ifndef SRC_TSOLLMENU_H_
#define SRC_TSOLLMENU_H_

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/label.h>

#include "Daten.h"

//XDieses Fenster kriegt eine Reference zu Dachgeschoss
//#include "Dachgeschoss.h" funktioniert nicht, da darin diese Class inkludiert ist
//Dann gäbe es eine Art Zirkel Inkludierung, die mein Compiler nicht auseinander kriegt...
//Deshalb muss eine "forward declaration" her:
class Dachgeschoss;

class tSollMenu : public Gtk::Window
{
  public:
    //RolladenMenu();
    tSollMenu(Dachgeschoss&);
    void set_ort(TEMP_ENUM wo, float old);
    void set_tSoll();

  private:
    //Referenz zur Mutterebene Dachgeschoss, damit dort eine Änderung der Rolläden ausgeführt werden kann
    Dachgeschoss& hauptEbene;

    //Sollwert für diesen Ort einstellen:
    TEMP_ENUM ort;
   
    Gtk::Grid grid_teilung_horizontal; 
    Gtk::Grid grid_teilung_vertikal; 

    Gtk::Label spacer_1, spacer_2, spacer_3;

    Gtk::Label bezeichnung;
    Glib::RefPtr<Gtk::Adjustment>  spinSettings;
    Gtk::SpinButton wert;
    Gtk::Button button_nehmen;
    Gtk::Button button_abbrechen;
};

#endif /* SRC_TSOLLMENU_H_ */
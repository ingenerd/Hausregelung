#include "RolladenMenu.h"
//Dachgeschoss.h muss inkludiert sein, damit Methoden der Referenz hauptEbene bekannt sind...
#include "Dachgeschoss.h"
#include <gtkmm/label.h>

/*RolladenMenu::RolladenMenu()
{
  set_resizable(false);
}*/

RolladenMenu::RolladenMenu(Dachgeschoss& mutter):hauptEbene{mutter}
{
  set_resizable(false);
  set_default_size(600,360);
  set_size_request(600,360);
  set_decorated(false);  
  set_position(Gtk::WIN_POS_CENTER);

  grid_haupt_teilung.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  grid_links.set_orientation(Gtk::ORIENTATION_VERTICAL);
  grid_mitte.set_orientation(Gtk::ORIENTATION_VERTICAL);
  grid_rechts.set_orientation(Gtk::ORIENTATION_VERTICAL);

  grid_haupt_teilung.add(grid_links);
  grid_haupt_teilung.add(grid_mitte);
  grid_haupt_teilung.add(grid_rechts);

  button_ausfuehren = Gtk::Button("Ausführen");
  test = Gtk::Label("upsi!");
  grid_mitte.add(test);
  grid_rechts.add(button_ausfuehren);

  add(grid_haupt_teilung);
  show_all_children();

  //ein Lambda-Ausdruck geht auch beim signal-connect
  //im Lambda-Ausdruck könnte der "public"-Funktion von hauptebene auch einfach Parameter übergeben werden...
  //button_ausfuehren.signal_clicked().connect([this](){hauptEbene.publicFunktion(parameter);});
  button_ausfuehren.signal_clicked().connect(sigc::mem_fun(hauptEbene,&Dachgeschoss::RolladenFahren));
}


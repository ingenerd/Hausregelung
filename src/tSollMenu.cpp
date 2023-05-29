#include "tSollMenu.h"
//Dachgeschoss.h muss inkludiert sein, damit Methoden der Referenz hauptEbene bekannt sind...
#include "Dachgeschoss.h"
#include <gtkmm/label.h>
#include <sstream>
#include <string>


tSollMenu::tSollMenu(Dachgeschoss& mutter) : hauptEbene{mutter}, spinSettings(Gtk::Adjustment::create(20.0,15.0,28.0,0.5,10.0,0.0)), wert(spinSettings,1.0,1)
{
  set_resizable(false);
  set_default_size(400,200);
  set_size_request(400,200);
  set_decorated(false);  
  set_position(Gtk::WIN_POS_CENTER);

  grid_haupt_teilung.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

  bezeichnung = Gtk::Label("leer");

  wert.set_numeric(true);
  wert.set_wrap(false);

  button_nehmen = Gtk::Button("setzen");
  
  grid_haupt_teilung.add(bezeichnung);
  grid_haupt_teilung.add(wert);
  grid_haupt_teilung.add(button_nehmen);

  add(grid_haupt_teilung);
  
  button_nehmen.signal_clicked().connect(sigc::mem_fun(*this,&tSollMenu::set_tSoll));
  //button_nehmen.signal_clicked().connect(sigc::bind(sigc::mem_fun(hauptEbene,&Dachgeschoss::set_tSoll),float(wert.get_value())));

  show_all_children();
}

void tSollMenu::set_ort(TEMP_ENUM wo)
{
  ort=wo;
  std::string ortName;
  switch(wo){
    case T_BAD_SOLL:  ortName = "Bad"        ; break;
    case T_ELT_SOLL:  ortName = "Eltern"     ; break;
    case T_KiVo_SOLL: ortName = "Kind vorne" ; break;
    case T_KiHi_SOLL: ortName = "Kind hinten"; break;
    default         : ortName = "FALSCHER PARAMETER";
  }

  std::stringstream ss;
  ss << "Temperatursollwert " << ortName << ": ";

  bezeichnung.set_text(ss.str());
}

void tSollMenu::set_tSoll()
{
  hauptEbene.get_allData().set_t(ort,float(wert.get_value()));
  hauptEbene.set_tSoll(float(wert.get_value()));
}
#include "tSollMenu.h"
//Dachgeschoss.h muss inkludiert sein, damit Methoden der Referenz hauptEbene bekannt sind...
#include "Dachgeschoss.h"
#include <gtkmm/label.h>
#include <sstream>
#include <string>


tSollMenu::tSollMenu(Dachgeschoss& mutter) : hauptEbene{mutter}, spinSettings(Gtk::Adjustment::create(20.0,15.0,28.0,0.5,10.0,0.0)), wert(spinSettings,1.0,1)
{
  set_resizable(false);
  set_default_size(400,-1);
  set_size_request(400,-1);
  set_decorated(false);  
  set_position(Gtk::WIN_POS_CENTER);
  set_border_width(15);

  grid_teilung_vertikal.set_orientation(Gtk::ORIENTATION_VERTICAL);
  grid_teilung_horizontal.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  
  Pango::FontDescription font;
  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_ULTRABOLD);
  font.set_size(14 * PANGO_SCALE);

  bezeichnung = Gtk::Label("leer");
  bezeichnung.set_halign(Gtk::ALIGN_CENTER);
  auto context = bezeichnung.get_pango_context();
  context->set_font_description(font);
  
  wert.set_numeric(true);
  wert.set_wrap(false);
  wert.set_hexpand(false);
  wert.set_halign(Gtk::ALIGN_CENTER);

  spacer_1 = Gtk::Label("");
  spacer_1.set_size_request(-1,15);
  spacer_2 = Gtk::Label("");
  spacer_2.set_size_request(-1,15);
  spacer_3 = Gtk::Label("");
  spacer_3.set_size_request(40,-1);

  button_nehmen = Gtk::Button("setzen");
  button_nehmen.set_size_request(120,-1);
  button_abbrechen = Gtk::Button("abbrechen");
  button_abbrechen.set_size_request(120,-1);
  
  grid_teilung_horizontal.add(button_abbrechen);
  grid_teilung_horizontal.add(spacer_3);
  grid_teilung_horizontal.add(button_nehmen);

  grid_teilung_horizontal.set_halign(Gtk::ALIGN_CENTER);

  grid_teilung_vertikal.add(bezeichnung);
  grid_teilung_vertikal.add(spacer_1);
  grid_teilung_vertikal.add(wert);
  grid_teilung_vertikal.add(spacer_2);
  grid_teilung_vertikal.add(grid_teilung_horizontal);
  grid_teilung_vertikal.set_halign(Gtk::ALIGN_CENTER);
  
  add(grid_teilung_vertikal);
  
  button_nehmen.signal_clicked().connect(sigc::mem_fun(*this,&tSollMenu::set_tSoll));
  //button_nehmen.signal_clicked().connect(sigc::bind(sigc::mem_fun(hauptEbene,&Dachgeschoss::set_tSoll),float(wert.get_value())));
  button_abbrechen.signal_clicked().connect([this](){hide();});

  show_all_children();
}

void tSollMenu::set_ort(TEMP_ENUM wo, float old)
{
  ort=wo;
  wert.set_value(double(old));
  std::string ortName;
  switch(wo){
    case T_BAD_SOLL : ortName = "Bad"        ; break;
    case T_ELT_SOLL : ortName = "Eltern"     ; break;
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
  //Die Daten aktualisieren sich über den MQTT Broker und müssen nicht explizit gesetzt werden
  //hauptEbene.get_allData().set_t(ort,float(wert.get_value()));
  hauptEbene.set_tSoll(ort, float(wert.get_value()));
  hide();
}
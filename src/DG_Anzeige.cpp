#include "DG_Anzeige.h"
#include "Dachgeschoss.h"
#include "definitions.h"

#include <iostream>
#include <iomanip>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <sstream>

DG_Anzeige::DG_Anzeige(std::shared_ptr<Daten>& data, Dachgeschoss &mutter) : allData(data) //Größe: 500 x 430 (Breite x Hoehe) Pixel
{
  set_size_request (BREITE-RAND-RAND-TOGGLEBREITE-TOGGLEBREITE-SPACER-SPACER-170, HOEHE-RAND-RAND-SPACER-30);

  pkt_t_Bad  = Punkt(133,220);
  pkt_t_KiVo = Punkt(133,100);
  pkt_t_KiHi = Punkt(340,100);
  pkt_t_Elt  = Punkt(340,250);

  pkt_r_Bad   = Punkt( 32,250);
  pkt_r_KiVo1 = Punkt( 32, 90);
  pkt_r_KiVo2 = Punkt( 32,140);
  pkt_r_KiHi1 = Punkt(462, 90);
  pkt_r_KiHi2 = Punkt(462,140);
  pkt_r_Elt   = Punkt(462,300);

  breiteBox = 30;

  aktModus = Visualisierung::Grundriss;

  //um Klicks (signals) in der DrawingArea verarbeiten zu können - die Maskierung ist standardmäßig zu klein für eine DrawingArea
  add_events(Gdk::BUTTON_PRESS_MASK);
  signal_button_press_event().connect(sigc::mem_fun(*this,&DG_Anzeige::on_anzeige_clicked));
  signal_tSollMenu.connect(sigc::mem_fun(mutter,&Dachgeschoss::tSoll_menu));

}

DG_Anzeige::~DG_Anzeige()
{
}

void DG_Anzeige::toggle_r_auswahl(ZimmerRolladen identifier)
{
  switch(identifier){
    case ZimmerRolladen::Bad_Roll:   allData->set_rWahl(R_Bad  ,!allData->get_rWahl(R_Bad  )); break;
    case ZimmerRolladen::KiVo1_Roll: allData->set_rWahl(R_KiVo1,!allData->get_rWahl(R_KiVo1)); break;
    case ZimmerRolladen::KiVo2_Roll: allData->set_rWahl(R_KiVo2,!allData->get_rWahl(R_KiVo2)); break;
    case ZimmerRolladen::KiHi1_Roll: allData->set_rWahl(R_KiHi1,!allData->get_rWahl(R_KiHi1)); break;
    case ZimmerRolladen::KiHi2_Roll: allData->set_rWahl(R_KiHi2,!allData->get_rWahl(R_KiHi2)); break;
    case ZimmerRolladen::Elt_Roll:   allData->set_rWahl(R_Elt  ,!allData->get_rWahl(R_Elt  )); break;
  }
}

void DG_Anzeige::set_modus(Visualisierung akt)
{
  aktModus = akt;
}

Visualisierung DG_Anzeige::get_modus()
{
  return (aktModus);
}

bool DG_Anzeige::on_anzeige_clicked(GdkEventButton* event) //Reaktion auf Klick in Anzeige
{
  // std::cout << "X: " << event->x << " - " << "Y: " << event->y << std::endl;

  Punkt Klick(int(event->x),int(event->y));
  if (get_modus() == Visualisierung::Grundriss) {
    if (Klick.drinnen(pkt_r_Bad,   breiteBox, breiteBox)) { toggle_r_auswahl(ZimmerRolladen::Bad_Roll); }
    if (Klick.drinnen(pkt_r_Elt,   breiteBox, breiteBox)) { toggle_r_auswahl(ZimmerRolladen::Elt_Roll); }
    if (Klick.drinnen(pkt_r_KiVo1, breiteBox, breiteBox)) { toggle_r_auswahl(ZimmerRolladen::KiVo1_Roll); }
    if (Klick.drinnen(pkt_r_KiVo2, breiteBox, breiteBox)) { toggle_r_auswahl(ZimmerRolladen::KiVo2_Roll); }
    if (Klick.drinnen(pkt_r_KiHi1, breiteBox, breiteBox)) { toggle_r_auswahl(ZimmerRolladen::KiHi1_Roll); }
    if (Klick.drinnen(pkt_r_KiHi2, breiteBox, breiteBox)) { toggle_r_auswahl(ZimmerRolladen::KiHi2_Roll); }

    if (Klick.drinnen(pkt_t_Bad , 100, 50)) { signal_tSollMenu.emit(T_BAD_SOLL ); }
    if (Klick.drinnen(pkt_t_Elt , 100, 50)) { signal_tSollMenu.emit(T_ELT_SOLL ); }
    if (Klick.drinnen(pkt_t_KiVo, 100, 50)) { signal_tSollMenu.emit(T_KiVo_SOLL); }
    if (Klick.drinnen(pkt_t_KiHi, 100, 50)) { signal_tSollMenu.emit(T_KiHi_SOLL); }
  }

  queue_draw();

  return true; //es scheint egal zu sein, was returniert wird... dieser Handler darf kein void sein - muss bool sein zum compilieren, aber verhält sich wie void...
}

bool DG_Anzeige::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  if (aktModus == Visualisierung::Grundriss) {zeigeGrundriss(cr);}
  if (aktModus == Visualisierung::Schema   ) {zeigeSchema(cr)   ;}

  return true;
}

void DG_Anzeige::zeigeSchema(const Cairo::RefPtr<Cairo::Context>& cr)
{
  //Gtk::Allocation allocation = get_allocation();
  //const int breite = allocation.get_width();
  //const int hoehe = allocation.get_height();

  auto hintergrund = Gdk::Pixbuf::create_from_file("/home/bejo/git/Hausregelung/style/Schema2.png");
  Gdk::Cairo::set_source_pixbuf(cr, hintergrund);
  cr->rectangle(0, 0, 530, 400);
  cr->fill();
}

void DG_Anzeige::zeigeGrundriss(const Cairo::RefPtr<Cairo::Context>& cr)
{
  auto hintergrund = Gdk::Pixbuf::create_from_file("/home/bejo/git/Hausregelung/style/DG_LBW_6.png");
  Gdk::Cairo::set_source_pixbuf(cr, hintergrund);
  cr->rectangle(0, 0, 500, 430);
  cr->fill();
  
  zeigeTemp(cr,allData->get_t(T_ELT_IST) ,allData->get_t(T_ELT_SOLL) ,pkt_t_Elt );
  zeigeTemp(cr,allData->get_t(T_BAD_IST) ,allData->get_t(T_BAD_SOLL) ,pkt_t_Bad );
  zeigeTemp(cr,allData->get_t(T_KiVo_IST),allData->get_t(T_KiVo_SOLL),pkt_t_KiVo);
  zeigeTemp(cr,allData->get_t(T_KiHi_IST),allData->get_t(T_KiHi_SOLL),pkt_t_KiHi);

  zeigeRolladenBox(cr, allData->get_rWahl(R_Bad  ), pkt_r_Bad  );
  zeigeRolladenBox(cr, allData->get_rWahl(R_KiVo1), pkt_r_KiVo1);
  zeigeRolladenBox(cr, allData->get_rWahl(R_KiVo2), pkt_r_KiVo2);
  zeigeRolladenBox(cr, allData->get_rWahl(R_KiHi1), pkt_r_KiHi1);
  zeigeRolladenBox(cr, allData->get_rWahl(R_KiHi2), pkt_r_KiHi2);
  zeigeRolladenBox(cr, allData->get_rWahl(R_Elt  ), pkt_r_Elt  );
}

void DG_Anzeige::zeigeRolladenBox(const Cairo::RefPtr<Cairo::Context>& cr, bool auswahl, Punkt pkt)
{
  cr->rectangle(pkt.get_x()-breiteBox/2, pkt.get_y()-breiteBox/2, breiteBox, breiteBox);
  cr->set_source_rgba(1,1,1,1);
  cr->fill();
  cr->rectangle(pkt.get_x()-breiteBox/2, pkt.get_y()-breiteBox/2, breiteBox, breiteBox);
  cr->set_line_width(3.0);
  cr->set_source_rgba(bjsGreyDark,1);
  cr->stroke();
  
  if (auswahl)
  {
    cr->move_to(pkt.get_x()-breiteBox/2-breiteBox/7,pkt.get_y()-breiteBox/2+breiteBox/5);
    cr->rel_line_to(breiteBox/2, breiteBox/2);
    cr->rel_line_to(breiteBox*0.55, -breiteBox);
    cr->set_line_width(5.0);
    cr->set_source_rgba(bjsGreenRegular,1);
    cr->stroke();
  }
}

void DG_Anzeige::zeigeTemp(const Cairo::RefPtr<Cairo::Context>& cr, float t_IST, float t_SOLL, Punkt pkt)
{
  #define color_IST_low bjsBlueRegular
  #define color_IST_high bjsRedRegular
  #define color_IST_good bjsGreenRegular
  #define color_Normal bjsOrangeRegular
  #define color_SOLL bjsOrangeRegular

  Pango::FontDescription font;

  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_ULTRABOLD);
  font.set_size(14 * PANGO_SCALE);

  int text_width;
  int text_height;
  
  std::stringstream aktString;
  aktString << std::fixed << std::setprecision(1) << t_IST;

  //T_IST
  auto layout = create_pango_layout(aktString.str());
  layout->set_font_description(font);
  layout->get_pixel_size(text_width, text_height);
  cr->move_to(pkt.get_x()-text_width*1.05,pkt.get_y()-text_height*0.85); 
  if (t_IST < t_SOLL && t_SOLL-t_IST > 2)
  {cr->set_source_rgba(color_IST_low,1);}
  else if (t_IST > t_SOLL && t_IST-t_SOLL > 2)
  {cr->set_source_rgba(color_IST_high,1);}
  else
  {cr->set_source_rgba(color_IST_good,1);}
  layout->show_in_cairo_context(cr);

  // Schrägstrich
  layout = create_pango_layout("/");
  font.set_size(20 * PANGO_SCALE);
  layout->set_font_description(font);
  layout->get_pixel_size(text_width, text_height);
  cr->move_to(pkt.get_x()-text_width/2,pkt.get_y()-text_height/2); 
  cr->set_source_rgba(color_Normal,1);
  layout->show_in_cairo_context(cr);

  //T_SOLL
  cr->move_to((pkt.get_x()+text_width/2*0), (pkt.get_y()+text_height/2*0));
  aktString.str(std::string()); // empty stringStream
  aktString << t_SOLL << "°C";
  layout = create_pango_layout(aktString.str());
  font.set_size(14 * PANGO_SCALE);
  layout->set_font_description(font);
  cr->set_source_rgba(color_SOLL,1);
  layout->show_in_cairo_context(cr); 
}
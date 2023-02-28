#include "Anzeige.h"
#include "definitions.h"

#include <iostream>
#include <iomanip>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <sstream>

Anzeige::Anzeige()
{
  set_size_request (530, 400);
  t_Elt_IST = -66.6;
  t_Elt_SOLL = 22.2;
  t_Bad_IST = -66.6;
  t_Bad_SOLL = 24.2;
  t_KiVo_IST = -66.6;
  t_KiVo_SOLL = 22.2;
  t_KiHi_IST = -66.6;
  t_KiHi_SOLL = 22.2;

  wahl_Bad = true;
  wahl_KiVo1 = true;
  wahl_KiVo2 = true;
  wahl_KiHi1 = true;
  wahl_KiHi2 = true;
  wahl_Elt = true;
  
  r_Bad = RolladenZust::voll_offen;
  r_KiVo1 = RolladenZust::voll_offen;
  r_KiVo2 = RolladenZust::voll_offen;
  r_KiHi1 = RolladenZust::voll_offen;
  r_KiHi2 = RolladenZust::voll_offen;
  r_Elt = RolladenZust::voll_offen;

  
  pkt_t_Bad  = Punkt(160,220);
  pkt_t_KiVo = Punkt(160,100);
  pkt_t_KiHi = Punkt(360,100);
  pkt_t_Elt  = Punkt(360,250);

  pkt_r_Bad   = Punkt( 25,240);
  pkt_r_KiVo1 = Punkt( 25, 60);
  pkt_r_KiVo2 = Punkt( 25,120);
  pkt_r_KiHi1 = Punkt(490, 60);
  pkt_r_KiHi2 = Punkt(490,120);
  pkt_r_Elt   = Punkt(490,270);

  breiteBox = 25;
  x_rBox_Bad = 25;
  y_rBox_Bad = 240;
  x_rBox_KiVo1 = 25;
  y_rBox_KiVo1 = 60;
  x_rBox_KiVo2 = 25;
  y_rBox_KiVo2 = 120;
  x_rBox_KiHi1 = 490;
  y_rBox_KiHi1 = 60;
  x_rBox_KiHi2 = 490;
  y_rBox_KiHi2 = 120;
  x_rBox_Elt = 490;
  y_rBox_Elt = 270;


  aktModus = Visualisierung::Grundriss;
  //um Klicks (signals) in der DrawingArea verarbeiten zu können - die Maskierung ist standardmäßig zu klein für eine DrawingArea
  add_events(Gdk::BUTTON_PRESS_MASK);
  //signal_button_press_event().connect(sigc::mem_fun(*this,&Anzeige::on_anzeige_clicked));
}

Anzeige::~Anzeige()
{
}

int Anzeige::get_pos(char Richtung, ZimmerRolladen identifier)
{
  int ret_x;
  int ret_y;
  switch(identifier){
  case ZimmerRolladen::Bad_Roll:   ret_x = x_rBox_Bad;   ret_y = y_rBox_Bad;   break;
  case ZimmerRolladen::KiVo1_Roll: ret_x = x_rBox_KiVo1; ret_y = y_rBox_KiVo1; break;
  case ZimmerRolladen::KiVo2_Roll: ret_x = x_rBox_KiVo2; ret_y = y_rBox_KiVo2; break;
  case ZimmerRolladen::KiHi1_Roll: ret_x = x_rBox_KiHi1; ret_y = y_rBox_KiHi1; break;
  case ZimmerRolladen::KiHi2_Roll: ret_x = x_rBox_KiHi2; ret_y = y_rBox_KiHi2; break;
  case ZimmerRolladen::Elt_Roll:   ret_x = x_rBox_Elt;   ret_y = y_rBox_Elt;   break;
  }
  if (Richtung=='x')
  {
    return(ret_x);
  } else
  {
    return(ret_y);
  }
}
int Anzeige::get_RollBoxBreite()
{
  return breiteBox;
}

void Anzeige::toggle_r_auswahl(ZimmerRolladen identifier)
{
  switch(identifier){
  case ZimmerRolladen::Bad_Roll:   wahl_Bad   = !wahl_Bad;   break;
  case ZimmerRolladen::KiVo1_Roll: wahl_KiVo1 = !wahl_KiVo1; break;
  case ZimmerRolladen::KiVo2_Roll: wahl_KiVo2 = !wahl_KiVo2; break;
  case ZimmerRolladen::KiHi1_Roll: wahl_KiHi1 = !wahl_KiHi1; break;
  case ZimmerRolladen::KiHi2_Roll: wahl_KiHi2 = !wahl_KiHi2; break;
  case ZimmerRolladen::Elt_Roll:   wahl_Elt   = !wahl_Elt;   break;
  }
}

void Anzeige::set_t(float value, ZimmerTemp identifier)
{
  switch(identifier){
  case ZimmerTemp::Elt_IST: t_Elt_IST = value; break;
  case ZimmerTemp::Elt_SOLL: t_Elt_SOLL = value; break;
  case ZimmerTemp::Bad_IST: t_Bad_IST = value; break;
  case ZimmerTemp::Bad_SOLL: t_Bad_SOLL = value; break;
  case ZimmerTemp::KiVo_IST: t_KiVo_IST = value; break;
  case ZimmerTemp::KiVo_SOLL: t_KiVo_SOLL = value; break;
  case ZimmerTemp::KiHi_IST: t_KiHi_IST = value; break;
  case ZimmerTemp::KiHi_SOLL: t_KiHi_SOLL = value; break;
  }
}

void Anzeige::set_modus(Visualisierung akt)
{
  aktModus = akt;
}

Visualisierung Anzeige::get_modus()
{
  return (aktModus);
}

bool Anzeige::on_anzeige_clicked(GdkEventButton* event) //Reaktion auf Klick in Anzeige
{
  std::cout << "DOPPELT!" << std::endl;
  return true;
}

bool Anzeige::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  if (aktModus == Visualisierung::Grundriss) {zeigeGrundriss(cr);}
  if (aktModus == Visualisierung::Schema) {zeigeSchema(cr);}

  return true;
}

void Anzeige::zeigeSchema(const Cairo::RefPtr<Cairo::Context>& cr)
{
  //Gtk::Allocation allocation = get_allocation();
  //const int breite = allocation.get_width();
  //const int hoehe = allocation.get_height();

  auto grundriss = Gdk::Pixbuf::create_from_file("/home/bejo/git/Hausregelung/style/Schema2.png");
  Gdk::Cairo::set_source_pixbuf(cr, grundriss);
  cr->rectangle(0, 0, 530, 400);
  cr->fill();
}

void Anzeige::zeigeGrundriss(const Cairo::RefPtr<Cairo::Context>& cr)
{
  auto grundriss = Gdk::Pixbuf::create_from_file("/home/bejo/git/Hausregelung/style/DG_LBW_3.png");
  Gdk::Cairo::set_source_pixbuf(cr, grundriss);
  cr->rectangle(0, 0, 530, 400);
  cr->fill();
  
  zeigeTemp(cr,t_Elt_IST,t_Elt_SOLL,pkt_t_Elt);
  zeigeTemp(cr,t_Bad_IST,t_Bad_SOLL,pkt_t_Bad);
  zeigeTemp(cr,t_KiVo_IST,t_KiVo_SOLL,pkt_t_KiVo);
  zeigeTemp(cr,t_KiHi_IST,t_KiHi_SOLL,pkt_t_KiHi);

  zeigeRolladenBox(cr, wahl_Bad, pkt_r_Bad);
  zeigeRolladenBox(cr, wahl_KiVo1, pkt_r_KiVo1);
  zeigeRolladenBox(cr, wahl_KiVo2, pkt_r_KiVo2);
  zeigeRolladenBox(cr, wahl_KiHi1, pkt_r_KiHi1);
  zeigeRolladenBox(cr, wahl_KiHi2, pkt_r_KiHi2);
  zeigeRolladenBox(cr, wahl_Elt, pkt_r_Elt);
}

void Anzeige::zeigeRolladenBox(const Cairo::RefPtr<Cairo::Context>& cr, bool auswahl, Punkt pkt)
{
  cr->rectangle(pkt.get_x(), pkt.get_y(), breiteBox, breiteBox);
  cr->set_source_rgba(1,1,1,1);
  cr->fill();
  cr->rectangle(pkt.get_x(), pkt.get_y(), breiteBox, breiteBox);
  cr->set_line_width(3.0);
  cr->set_source_rgba(bjsGreyDark,1);
  cr->stroke();
  
  if (auswahl)
  {
    cr->move_to(pkt.get_x()-breiteBox/7,pkt.get_y()+breiteBox/5);
    cr->rel_line_to(breiteBox/2, breiteBox/2);
    cr->rel_line_to(breiteBox*0.55, -breiteBox);
    cr->set_line_width(5.0);
    cr->set_source_rgba(bjsGreenRegular,1);
    cr->stroke();
  }
}

void Anzeige::zeigeTemp(const Cairo::RefPtr<Cairo::Context>& cr, float t_IST, float t_SOLL, Punkt pkt)
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
#include "Anzeige.h"
#include "bjsColors.h"

#include <iostream>
#include <iomanip>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <sstream>

Anzeige::Anzeige()
{
  set_size_request (495, 480);
  t_Elt_IST = 19;
  t_Elt_SOLL = 22.2;
}

Anzeige::~Anzeige()
{
}

void Anzeige::set_t_Elt_IST(float value)
{
   t_Elt_IST = value;
}

bool Anzeige::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  //Gtk::Allocation allocation = get_allocation();
  //const int breite = allocation.get_width();
  //const int hoehe = allocation.get_height();

  auto grundriss = Gdk::Pixbuf::create_from_file("/home/bejo/git/Hausregelung/style/DG_LBW_2.png");
  Gdk::Cairo::set_source_pixbuf(cr, grundriss);
  cr->rectangle(0, 0, 480, 800);
  cr->fill();
  
  // Bad
  zeigeTemp(cr,21.56,24,140,235);

  // Kind vorne
  zeigeTemp(cr,23.4,22,140,115);

  // Kind hinten
  zeigeTemp(cr,21,22,345,115);

  // Eltern
  zeigeTemp(cr,t_Elt_IST,t_Elt_SOLL,345,265);
  return true;
}

void Anzeige::zeigeTemp(const Cairo::RefPtr<Cairo::Context>& cr, float t_IST, float t_SOLL, int x, int y)
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
  cr->move_to(x-text_width*1.05,y-text_height*0.85); 
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
  cr->move_to(x-text_width/2,y-text_height/2); 
  cr->set_source_rgba(color_Normal,1);
  layout->show_in_cairo_context(cr);

  //T_SOLL
  cr->move_to((x+text_width/2*0), (y+text_height/2*0));
  aktString.str(std::string()); // empty stringStream
  aktString << t_SOLL << "°C";
  layout = create_pango_layout(aktString.str());
  font.set_size(14 * PANGO_SCALE);
  layout->set_font_description(font);
  cr->set_source_rgba(color_SOLL,1);
  layout->show_in_cairo_context(cr);
  
}
#include "Anzeige.h"
#include "bjsColors.h"

#include <iostream>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <sstream>

Anzeige::Anzeige()
{
  set_size_request (495, 400);
}

Anzeige::~Anzeige()
{
}

bool Anzeige::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int breite = allocation.get_width();
  const int hoehe = allocation.get_height();

  auto grundriss = Gdk::Pixbuf::create_from_file("/home/bejo/git/Hausregelung/style/test.jpeg");
  Gdk::Cairo::set_source_pixbuf(cr, grundriss);
  cr->rectangle(10, 10, 475, 380);
  cr->fill();
  
  zeigeTemp(cr,55.5,66.6,100,40);

  return true;
}

void Anzeige::zeigeTemp(const Cairo::RefPtr<Cairo::Context>& cr, double t_IST, double t_SOLL, int x, int y)
{
  #define color_IST bjsGreenRegular
  #define color_Normal bjsYellowRegular
  #define color_SOLL bjsRedRegular

  Pango::FontDescription font;

  font.set_family("Monospace");
  //font.set_weight(Pango::WEIGHT_ULTRABOLD);
  font.set_size(14 * PANGO_SCALE);

  int text_width;
  int text_height;
  
  std::stringstream aktString;
  aktString << t_IST;

  auto layout = create_pango_layout(aktString.str());
  layout->set_font_description(font);
  layout->get_pixel_size(text_width, text_height);
  cr->move_to(x-text_width*1.05,y-text_height*1.05); 
  cr->set_source_rgba(color_IST,1);
  layout->show_in_cairo_context(cr);

  layout = create_pango_layout("/");
  font.set_size(30 * PANGO_SCALE);
  layout->get_pixel_size(text_width, text_height);
  cr->move_to(x-text_width/2,y-text_height/2); 
  cr->set_source_rgba(color_Normal,1);
  layout->show_in_cairo_context(cr);

  
  cr->move_to((x+text_width/2), (y+text_height/2));

  aktString.str(std::string()); // empty stringStream
  aktString << t_SOLL;
  cr->set_source_rgba(color_SOLL,1);
  layout = create_pango_layout(aktString.str());
  layout->show_in_cairo_context(cr);
  
}
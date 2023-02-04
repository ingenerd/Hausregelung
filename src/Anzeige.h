// Anzeige.h
// Die Anzeige als DrawingArea links im goldenen Schnitt des Bildschirms

#ifndef SRC_ANZEIGE_H_
#define SRC_ANZEIGE_H_

#include "definitions.h"
#include <string>

#include <gtkmm/drawingarea.h>

class Anzeige : public Gtk::DrawingArea
{
public:
  Anzeige();
  virtual ~Anzeige(); 
  void set_t(float value, ZimmerTemp identifier);
  void set_modus(Visualisierung akt);
  Visualisierung get_modus();

private:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  void zeigeGrundriss(const Cairo::RefPtr<Cairo::Context>& cr);
  void zeigeSchema(const Cairo::RefPtr<Cairo::Context>& cr);
  void zeigeTemp(const Cairo::RefPtr<Cairo::Context>& cr, float t_IST, float t_SOLL, int x, int y);

  //Temperaturen
  float t_Bad_IST;
  float t_Bad_SOLL;
  float t_KiVo_IST;
  float t_KiVo_SOLL;
  float t_KiHi_IST;
  float t_KiHi_SOLL;
  float t_Elt_IST;
  float t_Elt_SOLL;

  //aktuelle Ansicht
  Visualisierung aktModus;
};

#endif /* SRC_ANZEIGE_H_ */
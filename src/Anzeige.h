// Anzeige.h
// Die Anzeige als DrawingArea links im goldenen Schnitt des Bildschirms

#ifndef SRC_ANZEIGE_H_
#define SRC_ANZEIGE_H_

#include <gtkmm/drawingarea.h>

class Anzeige : public Gtk::DrawingArea
{
public:
  Anzeige();
  virtual ~Anzeige(); 
  void set_t_Elt_IST(float);

private:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  void zeigeTemp(const Cairo::RefPtr<Cairo::Context>& cr, float t_IST, float t_SOLL, int x, int y);

  //member data
  float t_Bad_IST;
  float t_Bad_SOLL;
  float t_KiVo_IST;
  float t_KiVo_SOLL;
  float t_KiHi_IST;
  float t_KiHi_SOLL;
  float t_Elt_IST;
  float t_Elt_SOLL;
};

#endif /* SRC_ANZEIGE_H_ */
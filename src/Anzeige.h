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

private:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  void zeigeTemp(const Cairo::RefPtr<Cairo::Context>& cr, double t_IST, double t_SOLL, int x, int y);
};

#endif /* SRC_ANZEIGE_H_ */
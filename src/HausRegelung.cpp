#include "Dachgeschoss.h"
#include <gtkmm/application.h>

int main (int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "LBW.Dachgeschoss");

  Dachgeschoss dachgeschoss;
  
  //Shows the window and returns when it is closed.
  return app->run(dachgeschoss);
}

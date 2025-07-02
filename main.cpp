#include <gtkmm.h>
#include "src/MainWindow.h"

int main() {
    auto app = Gtk::Application::create("org.digitallogic.suite");
    MainWindow window;
    return app->run(window);
}
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow();

protected:
    // Signal handlers
    void on_menu_file_new();
    void on_menu_file_open();
    void on_menu_file_save();
    void on_menu_file_quit();
    void on_menu_help_about();
    
    void on_tool_gate_clicked(const Glib::ustring& gate_type);
    bool on_canvas_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    
    // Helper methods
    void setup_menu_bar();
    void setup_toolbar();
    void setup_toolbox();
    void setup_canvas();

    // Member widgets
    Gtk::Box m_main_box;
    Gtk::MenuBar m_menu_bar;
    Gtk::Toolbar m_toolbar;
    Gtk::HPaned m_paned;
    Gtk::ScrolledWindow m_scrolled_window;
    Gtk::DrawingArea m_canvas;
    Gtk::VBox m_toolbox;
    
    // Menu items
    Gtk::MenuItem m_menu_file;
    Gtk::Menu m_submenu_file;
    Gtk::MenuItem m_menu_file_new;
    Gtk::MenuItem m_menu_file_open;
    Gtk::MenuItem m_menu_file_save;
    Gtk::SeparatorMenuItem m_menu_separator;
    Gtk::MenuItem m_menu_file_quit;
    
    Gtk::MenuItem m_menu_help;
    Gtk::Menu m_submenu_help;
    Gtk::MenuItem m_menu_help_about;
    
    // Toolbar buttons
    Gtk::ToolButton m_tool_and_gate;
    Gtk::ToolButton m_tool_or_gate;
    Gtk::ToolButton m_tool_not_gate;
    Gtk::ToolButton m_tool_nand_gate;
    Gtk::ToolButton m_tool_nor_gate;
    Gtk::ToolButton m_tool_xor_gate;
    Gtk::SeparatorToolItem m_tool_separator;
    Gtk::ToolButton m_tool_wire;
    
    // Status bar
    Gtk::Statusbar m_status_bar;
};

#endif // MAINWINDOW_H
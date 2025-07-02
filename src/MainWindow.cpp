#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow()
    : m_main_box(Gtk::ORIENTATION_VERTICAL),
      m_paned(),
      m_toolbox(Gtk::ORIENTATION_VERTICAL) {
    
    // Set window properties
    set_title("Digital Logic v2");
    set_default_size(1000, 700);
    set_position(Gtk::WIN_POS_CENTER);
    
    // Create main layout
    add(m_main_box);
    
    // Setup menu bar
    setup_menu_bar();
    m_main_box.pack_start(m_menu_bar, Gtk::PACK_SHRINK);
    
    // Setup toolbar
    setup_toolbar();
    m_main_box.pack_start(m_toolbar, Gtk::PACK_SHRINK);
    
    // Setup main content area with paned layout
    m_main_box.pack_start(m_paned, Gtk::PACK_EXPAND_WIDGET);
    
    // Setup toolbox (left panel)
    setup_toolbox();
    m_paned.pack1(m_toolbox, false, false);
    
    // Setup canvas (right panel)
    setup_canvas();
    m_paned.pack2(m_scrolled_window, true, false);
    
    // Setup status bar
    m_status_bar.push("Ready");
    m_main_box.pack_start(m_status_bar, Gtk::PACK_SHRINK);
    
    // Show all widgets
    show_all_children();
}

MainWindow::~MainWindow() {
}

void MainWindow::setup_menu_bar() {
    // File menu
    m_menu_file.set_label("File");
    m_menu_bar.append(m_menu_file);
    m_menu_file.set_submenu(m_submenu_file);
    
    m_menu_file_new.set_label("New");
    m_menu_file_new.signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::on_menu_file_new));
    m_submenu_file.append(m_menu_file_new);
    
    m_menu_file_open.set_label("Open");
    m_menu_file_open.signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::on_menu_file_open));
    m_submenu_file.append(m_menu_file_open);
    
    m_menu_file_save.set_label("Save");
    m_menu_file_save.signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::on_menu_file_save));
    m_submenu_file.append(m_menu_file_save);
    
    m_submenu_file.append(m_menu_separator);
    
    m_menu_file_quit.set_label("Quit");
    m_menu_file_quit.signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::on_menu_file_quit));
    m_submenu_file.append(m_menu_file_quit);
    
    // Help menu
    m_menu_help.set_label("Help");
    m_menu_bar.append(m_menu_help);
    m_menu_help.set_submenu(m_submenu_help);
    
    m_menu_help_about.set_label("About");
    m_menu_help_about.signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::on_menu_help_about));
    m_submenu_help.append(m_menu_help_about);
}

void MainWindow::setup_toolbar() {
    // Logic gate tools
    m_tool_and_gate.set_label("AND");
    m_tool_and_gate.set_tooltip_text("AND Gate");
    m_tool_and_gate.signal_clicked().connect(
        sigc::bind(sigc::mem_fun(*this, &MainWindow::on_tool_gate_clicked), "AND"));
    m_toolbar.append(m_tool_and_gate);
    
    m_tool_or_gate.set_label("OR");
    m_tool_or_gate.set_tooltip_text("OR Gate");
    m_tool_or_gate.signal_clicked().connect(
        sigc::bind(sigc::mem_fun(*this, &MainWindow::on_tool_gate_clicked), "OR"));
    m_toolbar.append(m_tool_or_gate);
    
    m_tool_not_gate.set_label("NOT");
    m_tool_not_gate.set_tooltip_text("NOT Gate");
    m_tool_not_gate.signal_clicked().connect(
        sigc::bind(sigc::mem_fun(*this, &MainWindow::on_tool_gate_clicked), "NOT"));
    m_toolbar.append(m_tool_not_gate);
    
    m_tool_nand_gate.set_label("NAND");
    m_tool_nand_gate.set_tooltip_text("NAND Gate");
    m_tool_nand_gate.signal_clicked().connect(
        sigc::bind(sigc::mem_fun(*this, &MainWindow::on_tool_gate_clicked), "NAND"));
    m_toolbar.append(m_tool_nand_gate);
    
    m_tool_nor_gate.set_label("NOR");
    m_tool_nor_gate.set_tooltip_text("NOR Gate");
    m_tool_nor_gate.signal_clicked().connect(
        sigc::bind(sigc::mem_fun(*this, &MainWindow::on_tool_gate_clicked), "NOR"));
    m_toolbar.append(m_tool_nor_gate);
    
    m_tool_xor_gate.set_label("XOR");
    m_tool_xor_gate.set_tooltip_text("XOR Gate");
    m_tool_xor_gate.signal_clicked().connect(
        sigc::bind(sigc::mem_fun(*this, &MainWindow::on_tool_gate_clicked), "XOR"));
    m_toolbar.append(m_tool_xor_gate);
    
    m_toolbar.append(m_tool_separator);
    
    m_tool_wire.set_label("Wire");
    m_tool_wire.set_tooltip_text("Connect with Wire");
    m_tool_wire.signal_clicked().connect(
        sigc::bind(sigc::mem_fun(*this, &MainWindow::on_tool_gate_clicked), "WIRE"));
    m_toolbar.append(m_tool_wire);
}

void MainWindow::setup_toolbox() {
    m_toolbox.set_size_request(200, -1);
    
    auto label = Gtk::make_managed<Gtk::Label>("Components");
    label->set_markup("<b>Logic Gates</b>");
    m_toolbox.pack_start(*label, Gtk::PACK_SHRINK);
    
    // Add some spacing and information
    auto info_label = Gtk::make_managed<Gtk::Label>();
    info_label->set_markup("Select a gate from the toolbar\nand click on the canvas\nto place it.");
    info_label->set_line_wrap(true);
    m_toolbox.pack_start(*info_label, Gtk::PACK_SHRINK);
}

void MainWindow::setup_canvas() {
    m_canvas.set_size_request(600, 400);
    m_canvas.signal_draw().connect(
        sigc::mem_fun(*this, &MainWindow::on_canvas_draw));
    
    m_scrolled_window.add(m_canvas);
    m_scrolled_window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
}

// Signal handlers
void MainWindow::on_menu_file_new() {
    m_status_bar.pop();
    m_status_bar.push("New circuit created");
    std::cout << "New circuit" << std::endl;
}

void MainWindow::on_menu_file_open() {
    auto dialog = Gtk::FileChooserDialog(*this, "Open Circuit File");
    dialog.set_transient_for(*this);
    
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    
    auto filter_circuit = Gtk::FileFilter::create();
    filter_circuit->set_name("Circuit files");
    filter_circuit->add_pattern("*.dls");
    dialog.add_filter(filter_circuit);
    
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);
    
    int result = dialog.run();
    if (result == Gtk::RESPONSE_OK) {
        m_status_bar.pop();
        m_status_bar.push("Opened: " + dialog.get_filename());
        std::cout << "File selected: " << dialog.get_filename() << std::endl;
    }
}

void MainWindow::on_menu_file_save() {
    auto dialog = Gtk::FileChooserDialog(*this, "Save Circuit File", Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);
    
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Save", Gtk::RESPONSE_OK);
    
    auto filter_circuit = Gtk::FileFilter::create();
    filter_circuit->set_name("Circuit files");
    filter_circuit->add_pattern("*.dls");
    dialog.add_filter(filter_circuit);
    
    int result = dialog.run();
    if (result == Gtk::RESPONSE_OK) {
        m_status_bar.pop();
        m_status_bar.push("Saved: " + dialog.get_filename());
        std::cout << "File saved: " << dialog.get_filename() << std::endl;
    }
}

void MainWindow::on_menu_file_quit() {
    hide();
}

void MainWindow::on_menu_help_about() {
    auto dialog = Gtk::AboutDialog();
    dialog.set_transient_for(*this);
    dialog.set_program_name("Digital Logic Suite");
    dialog.set_version("1.0");
    dialog.set_copyright("Copyright © 2025");
    dialog.set_comments("A digital logic circuit design and simulation tool");
    dialog.set_license_type(Gtk::LICENSE_GPL_3_0);
    
    dialog.run();
}

void MainWindow::on_tool_gate_clicked(const Glib::ustring& gate_type) {
    m_status_bar.pop();
    m_status_bar.push("Selected: " + gate_type + " gate - Click on canvas to place");
    std::cout << "Tool selected: " << gate_type << std::endl;
}

bool MainWindow::on_canvas_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // Get the canvas dimensions
    Gtk::Allocation allocation = m_canvas.get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    
    // Clear the canvas with white background
    cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->paint();
    
    // Draw grid
    cr->set_source_rgb(0.9, 0.9, 0.9);
    cr->set_line_width(1.0);
    
    // Vertical grid lines
    for (int x = 0; x < width; x += 20) {
        cr->move_to(x, 0);
        cr->line_to(x, height);
    }
    
    // Horizontal grid lines
    for (int y = 0; y < height; y += 20) {
        cr->move_to(0, y);
        cr->line_to(width, y);
    }
    cr->stroke();
    
    // Draw a sample AND gate as demonstration
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->set_line_width(2.0);
    
    // AND gate body
    cr->move_to(100, 100);
    cr->line_to(140, 100);
    cr->arc(140, 115, 15, -M_PI_2, M_PI_2);
    cr->line_to(100, 130);
    cr->close_path();
    cr->stroke();
    
    // Input lines
    cr->move_to(80, 110);
    cr->line_to(100, 110);
    cr->move_to(80, 120);
    cr->line_to(100, 120);
    
    // Output line
    cr->move_to(155, 115);
    cr->line_to(175, 115);
    cr->stroke();
    
    // Add label
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->move_to(110, 145);
    cr->show_text("AND");
    
    return true;
}
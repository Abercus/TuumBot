/**
 * @file MainWindow.hpp
 * Experimental GUI application main window.
 *
 * @authors Ants-Oskar Mäesalu
 * @version 0.1
 */

#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <gtkmm.h>


class MainWindow: public Gtk::Window {

  public:
    MainWindow();
    virtual ~MainWindow();

  protected:
    Gtk::Grid grid;

    // Frames and boxes for the layout
    Gtk::Box drawingButtonsBox;
    Gtk::Box generalButtonsBox;
    Gtk::Frame imageBeforeFrame;
    Gtk::Frame imageAfterFrame;
    Gtk::Box imageBeforeOptionsBox;
    Gtk::Box imageAfterOptionsBox;

    // Drawing buttons and labels
    Gtk::Label entityChooseLabel;
    Gtk::ComboBoxText entityChooseComboBox;
    Gtk::Label brushSizeLabel;
    Gtk::Scale brushSizeScale;

    // General buttons
    Gtk::ComboBoxText fileChooseComboBox;
    Gtk::Button saveButton;
    Gtk::Button exitButton;

    // Options buttons
    Gtk::CheckButton displayMaskBeforeButton;
    Gtk::CheckButton displayMaskAfterButton;

  private:
    void setProperties();

    void construct();
    void constructGrid();

    void constructDrawingButtonsBox();
    void constructGeneralButtonsBox();
    void constructImageBeforeFrame();
    void constructImageAfterFrame();
    void constructImageBeforeOptionsBox();
    void constructImageAfterOptionsBox();

    void constructEntityChooseComboBox(Gtk::Container&);
    void constructBrushSizeScale(Gtk::Container&);
    void constructFileChooseComboBox(Gtk::Container&);
    void constructSaveButton(Gtk::Container&);
    void constructExitButton(Gtk::Container&);

};

#endif // GUI_MAIN_WINDOW_H

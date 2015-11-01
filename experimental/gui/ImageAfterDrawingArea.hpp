/**
 * @file ImageDrawingArea.hpp
 * Experimental GUI color calibration application "after" image drawing area.
 *
 * @authors Ants-Oskar Mäesalu
 * @version 0.1
 */

#ifndef GUI_IMAGE_AFTER_DRAWING_AREA_H
#define GUI_IMAGE_AFTER_DRAWING_AREA_H

#include <map>
#include <vector>

#include <gtkmm.h>
#include <gdkmm/pixbuf.h>

#include "ImageDrawingArea.hpp"


class ImageAfterDrawingArea: public ImageDrawingArea {

  public:
    ImageAfterDrawingArea(MainWindow*, Gtk::Scale*);
    virtual ~ImageAfterDrawingArea();

    void calculateFilterBuffer(const std::vector<std::vector<bool>>&, const std::vector<std::vector<bool>>&);
    void addBufferToFilter();

  protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>&);
    virtual bool on_scroll_event(GdkEventScroll*);

  private:
    Glib::RefPtr<Gdk::Pixbuf> image;
    Glib::RefPtr<Gdk::Pixbuf> filteredImage;

    Gtk::Scale *deltaScale;

    std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>> filter;
    std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>> filterAdditionBuffer;
    std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>> filterRemovalBuffer;

    void initialiseProperties();
    void initialiseImage();
    void initialiseDeltaScale(Gtk::Scale*);
    void initialiseFilters();

    void initialiseFilterMap(std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>>&);
    void initialiseFilter();
    void initialiseFilterAdditionBuffer();
    void initialiseFilterRemovalBuffer();

    void resetFilterMap(std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>>&);
    void resetFilter();
    void resetFilterAdditionBuffer();
    void resetFilterRemovalBuffer();

    bool applyFilter();
    bool drawImage(const Cairo::RefPtr<Cairo::Context>&);

    void calculateFilterBuffer(const std::vector<std::vector<bool>>&, std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>>&);
    void calculateFilterAdditionBuffer(const std::vector<std::vector<bool>>&);
    void calculateFilterRemovalBuffer(const std::vector<std::vector<bool>>&);

    void addBufferToFilter(std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>>&, const bool&);
    void addAdditionBufferToFilter();
    void addRemovalBufferToFilter();

};

#endif // GUI_IMAGE_AFTER_DRAWING_AREA_H

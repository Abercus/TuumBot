/**
 * @file ImageDrawingArea.hpp
 * Experimental GUI color calibration application "before" image drawing area.
 *
 * @authors Ants-Oskar Mäesalu
 * @version 0.1
 */

#ifndef GUI_IMAGE_BEFORE_DRAWING_AREA_H
#define GUI_IMAGE_BEFORE_DRAWING_AREA_H

#include <vector>
#include <gdkmm/pixbuf.h>

#include "ImageDrawingArea.hpp"


class ImageBeforeDrawingArea: public ImageDrawingArea {

  public:
    ImageBeforeDrawingArea();
    virtual ~ImageBeforeDrawingArea();

    bool maskEmpty() const;

  protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>&);

  private:
    Glib::RefPtr<Gdk::Pixbuf> image;

    std::vector<std::vector<bool>> mask;

    void initialiseMask();
    bool drawImage(const Cairo::RefPtr<Cairo::Context>&);
    bool applyMask();

};

#endif // GUI_IMAGE_BEFORE_DRAWING_AREA_H

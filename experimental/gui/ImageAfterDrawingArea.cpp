/**
 * @file ImageDrawingArea.cpp
 * Experimental GUI color calibration application "after" image drawing area.
 *
 * @authors Ants-Oskar Mäesalu
 * @version 0.1
 */

#include "ImageAfterDrawingArea.hpp"

#include "MainWindow.hpp"

#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <gdkmm/pixbuf.h>
#include <glibmm/refptr.h>
#include <glibmm/fileutils.h>

#include <iostream>


ImageAfterDrawingArea::ImageAfterDrawingArea(MainWindow *mainWindow, Gtk::Scale *deltaScale):
  ImageDrawingArea(mainWindow)
{
  initialiseProperties();
  initialiseImage();
  initialiseDeltaScale(deltaScale);
  initialiseFilters();
}

ImageAfterDrawingArea::~ImageAfterDrawingArea() {
  // Nothing to do here
}

void ImageAfterDrawingArea::calculateFilterBuffer(const std::vector<std::set<unsigned int>> &additionMaskList, const std::vector<std::set<unsigned int>> &removalMaskList) {
  resetFilterBuffers();

  unsigned int mode = mainWindow->getMode();

  guint8 *pixels = image->get_pixels();
  unsigned int channels = image->get_n_channels();
  unsigned int stride = image->get_rowstride();

  for (std::set<unsigned int>::iterator i = additionMaskList[mode].begin(); i != additionMaskList[mode].end(); ++i) {
    guint8 *pixel = pixels + ((*i) % 640) * channels + ((*i) / 640) * stride;
    filterAdditionBuffer[mode][pixel[0]][pixel[1]][pixel[2]] = true;
    filterAdditionBufferList[mode].insert(pixel[0] * 256 * 256 + pixel[1] * 256 + pixel[2]);
  }

  for (std::set<unsigned int>::iterator i = removalMaskList[mode].begin(); i != removalMaskList[mode].end(); ++i) {
    guint8 *pixel = pixels + ((*i) % 640) * channels + ((*i) / 640) * stride;
    filterRemovalBuffer[mode][pixel[0]][pixel[1]][pixel[2]] = true;
    filterRemovalBufferList[mode].insert(pixel[0] * 256 * 256 + pixel[1] * 256 + pixel[2]);
  }

  // Redraw
  queue_draw();
}

void ImageAfterDrawingArea::addBufferToFilter() {
  unsigned int mode = mainWindow->getMode();

  for (std::set<unsigned int>::iterator i = filterRemovalBufferList[mode].begin(); i != filterRemovalBufferList[mode].end(); ++i) {
    filter[mode][(*i) / 256 / 256][(*i) / 256 % 256][(*i) % 256] = false;
  }

  for (std::set<unsigned int>::iterator i = filterAdditionBufferList[mode].begin(); i != filterAdditionBufferList[mode].end(); ++i) {
    filter[mode][(*i) / 256 / 256][(*i) / 256 % 256][(*i) % 256] = true;
  }

  resetFilterBuffers();

  // Redraw
  queue_draw();
}

bool ImageAfterDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cairo) {
  if (!applyFilter())
    return false;

  if (!drawImage(cairo))
    return false;

  cairo->paint();

  return true;
}

bool ImageAfterDrawingArea::on_scroll_event(GdkEventScroll *scrollEvent) {
  if (scrollEvent->direction == GDK_SCROLL_UP) {
    if (deltaScale->get_value() < deltaScale->get_adjustment()->property_upper()) {
      deltaScale->set_value(deltaScale->get_value() + deltaScale->get_adjustment()->get_step_increment());
    }
  } else if (scrollEvent->direction == GDK_SCROLL_DOWN) {
    if (deltaScale->get_value() > deltaScale->get_adjustment()->property_lower()) {
      deltaScale->set_value(deltaScale->get_value() - deltaScale->get_adjustment()->get_step_increment());
    }
  }
  return true;
}

void ImageAfterDrawingArea::initialiseProperties() {
  set_size_request(640, 480);
}

void ImageAfterDrawingArea::initialiseImage() {
  image = Gdk::Pixbuf::create_from_file("frame.ppm"); // TODO: Remove association with files

  // Show the whole image
  if (image)
    set_size_request(image->get_width(), image->get_height());
}

void ImageAfterDrawingArea::initialiseDeltaScale(Gtk::Scale *deltaScale) {
  this->deltaScale = deltaScale;
  // TODO: Define exact usage
}

void ImageAfterDrawingArea::initialiseFilters() {
  initialiseFilter();
  initialiseFilterBuffers();
}

void ImageAfterDrawingArea::initialiseSingleFilterMap(std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>> &filterMap) {
  filterMap.clear();
  std::map<unsigned int, bool> subSubFilter;
  for (unsigned int i = 0; i < 256; ++i) {
    subSubFilter[i] = false;
  }
  std::map<unsigned int, std::map<unsigned int, bool>> subFilter;
  for (unsigned int i = 0; i < 256; ++i) {
    subFilter[i] = subSubFilter;
  }
  for (unsigned int i = 0; i < 256; ++i) {
    filterMap[i] = subFilter;
  }
}

void ImageAfterDrawingArea::initialiseFilterMap(std::vector<std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>>> &filterMap) {
  std::cout << "C1" << std::endl;
  std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>> singleFilterMap;
  std::cout << "C2" << std::endl;
  initialiseSingleFilterMap(singleFilterMap);
  std::cout << "C3" << std::endl;
  for (unsigned int i = 0; i < mainWindow->getModes().size(); ++i) {
    std::cout << "C4" << std::endl;
    filterMap.push_back(singleFilterMap);
    std::cout << "C5" << std::endl;
  }
  std::cout << "C6" << std::endl;
}

void ImageAfterDrawingArea::initialiseFilter() {
  initialiseFilterMap(filter);
}

void ImageAfterDrawingArea::initialiseFilterBuffers() {
  initialiseFilterAdditionBuffer();
  filterRemovalBuffer = filterAdditionBuffer;
}

void ImageAfterDrawingArea::initialiseFilterAdditionBuffer() {
  initialiseFilterMap(filterAdditionBuffer);
}

void ImageAfterDrawingArea::initialiseFilterRemovalBuffer() {
  initialiseFilterMap(filterRemovalBuffer);
}

void ImageAfterDrawingArea::initialiseResettedFilter() {
  initialiseSingleFilterMap(resettedFilter);
}

void ImageAfterDrawingArea::resetSingleFilterMap(std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>> &filterMap) {
  filterMap = resettedFilter;
}

void ImageAfterDrawingArea::resetFilterMap(std::vector<std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, bool>>>> &filterMap) {
  for (unsigned int i = 0; i < filterMap.size(); ++i) {
    resetSingleFilterMap(filterMap[i]);
  }
}

void ImageAfterDrawingArea::resetFilter() {
  resetFilterMap(filter);
}

void ImageAfterDrawingArea::resetFilterBuffers() {
  unsigned int mode = mainWindow->getMode();
  filterAdditionBuffer[mode] = resettedFilter;
  filterRemovalBuffer[mode] = resettedFilter;
  filterAdditionBufferList[mode].clear();
  filterRemovalBufferList[mode].clear();
}

void ImageAfterDrawingArea::resetFilterAdditionBuffer() {
  resetFilterMap(filterAdditionBuffer);
}

void ImageAfterDrawingArea::resetFilterRemovalBuffer() {
  resetFilterMap(filterRemovalBuffer);
}

bool ImageAfterDrawingArea::applyFilter() {
  filteredImage = image->copy(); // TODO: Copy only where is necessary (?)

  unsigned int mode = mainWindow->getMode();

  guint8 *pixels = filteredImage->get_pixels();
  unsigned int channels = filteredImage->get_n_channels();
  unsigned int stride = filteredImage->get_rowstride();

  // Color pixels
  for (unsigned int i = 0; i < 640; ++i) {
    for (unsigned int j = 0; j < 480; ++j) {
      guint8 *pixel = pixels + i * channels + j * stride;
      if ((filter[mode][pixel[0]][pixel[1]][pixel[2]] && !filterRemovalBuffer[mode][pixel[0]][pixel[1]][pixel[2]]) || filterAdditionBuffer[mode][pixel[0]][pixel[1]][pixel[2]]) {
        pixel[0] *= 0.3;
        pixel[1] *= 0.3;
        pixel[2] *= 0.3;
      }
    }
  }

  return true;
}

bool ImageAfterDrawingArea::drawImage(const Cairo::RefPtr<Cairo::Context> &cairo) {
  if (!filteredImage)
    return false;

  Gdk::Cairo::set_source_pixbuf(cairo, filteredImage, 0, 0);

  return true;
}

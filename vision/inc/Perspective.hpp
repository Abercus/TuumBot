/**
 *  @file Perspective.hpp
 *  Perspective class for coordinate mapping.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 3 December 2015
 */

#ifndef RTX_VISION_PERSPECTIVE_H
#define RTX_VISION_PERSPECTIVE_H

#include "Point2D.hpp"

#include <utility>


namespace rtx { namespace Vision { namespace Perspective {

  extern double A;
  extern double B;
  extern double C;

  // TODO: Maybe move samples here?

  // TODO: Use point class

  std::pair<double, double> virtualToReal(const unsigned int&, const unsigned int&);
  std::pair<double, double> virtualToReal(const std::pair<unsigned int, unsigned int>&);
  std::pair<double, double> virtualToReal(const Point2D*);

  std::pair<unsigned int, unsigned int> realToVirtual(const double&, const double&);
  std::pair<unsigned int, unsigned int> realToVirtual(const std::pair<double, double>&);

}}}

#endif // RTX_VISION_PERSPECTIVE_H

/**
 *  @file Goal.cpp
 *  Goal class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.2
 *  @date 2 December 2015
 */

#include "Goal.hpp"

#include "Color.hpp"


namespace rtx {

  Goal::Goal(Goal &other):
    Entity(*other.getTransform()),
    Rectangle(other.getWidth(), other.getLength()),
    blob(other.getBlob())
  {

  }

  Goal::Goal(const Transform transform, const Blob &blob, const double &width, const double &length):
    Entity(transform),
    Rectangle(width, length),
    blob(blob)
  {

  }

  Color Goal::getColor() const {
    return blob->getColor();
  }

  bool Goal::isBlue() const {
    return blob->isBlue();
  }

  bool Goal::isYellow() const {
    return blob->isYellow();
  }

}

/**
 *  @file Ball.cpp
 *  Ball class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.2
 *  @date 2 December 2015
 */

#include "Ball.hpp"


namespace rtx {

  Ball::Ball(Ball &other):
    Entity(*other.getTransform()),
    Circle(other.getRadius())
  {
    // Nothing to do here
  }

  Ball::Ball(const Transform transform, const double &radius):
    Entity(transform),
    Circle(radius)
  {
    // Nothing to do here
  }

  bool Ball::isInGoal() {
    // TODO
    return false;
  }

  bool Ball::isOutOfGoal() {
    return !isInGoal();
  }

  bool Ball::isInBounds() {
    // TODO
    return true;
  }

  bool Ball::isOutOfBounds() {
    return !isInBounds();
  }

  bool Ball::isKicked() {
    // TODO
    return false;
  }

  bool Ball::isNotKicked() {
    return !isKicked();
  }

  bool Ball::isValid() {
    // TODO
    return true;
  }

  bool Ball::isNotValid() {
    return !isValid();
  }

  bool Ball::setKicked(const bool &value) {
    kicked = value;
  }

  bool Ball::setInGoal(const bool &value) {
    inGoal = value;
  }

  bool Ball::setInBounds(const bool &value) {
    inBounds = value;
  }

}

/**
 * Tuum
 * Robotex 2015
 * University of Tartu
 * Team:
 *   Kristjan Kanarbik
 *   Meelik Kiik
 *   Ants-Oskar Mäesalu
 *   Mart Müllerbeck
 *   Kaur Viiklaid
 *   Indrek Virro
 *   Mihkel Väljaots

 * Ball class
 * Contributors:
 *   Ants-Oskar Mäesalu
 */

#include "ball.h"

Ball::Ball(const Ball& other):
Circle(other.getRadius()),
position{new Point2D(other.getPosition()->getX(), other.getPosition()->getY())}
{}

Ball::Ball(const Point2D* position, const double& radius):
Circle(radius),
position{new Point2D(position->getX(), position->getY())}
{}

void Ball::setPosition(const Point2D* position) {
  this->position = new Point2D(position->getX(), position->getY());
}

void Ball::setPosition(const double& x, const double& y) {
  this->position = new Point2D(x, y);
}

Point2D* Ball::getPosition() const {
  return position;
}

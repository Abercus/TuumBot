/**
 *  @file Ball.hpp
 *  Ball class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.2
 *  @date 2 December 2015
 */

#ifndef RTX_ENTITIES_BALL_H
#define RTX_ENTITIES_BALL_H

#include "Circle.hpp"
#include "Point2D.hpp"

#include "entityConstants.hpp"
#include "Entity.hpp"
#include "RelativePosition.hpp"


namespace rtx {

  class Ball: public Entity, public Circle {
    public:
      Ball(Ball&);
      Ball(const Transform, const double& = BALL_DIAMETER / 2.0);

      bool isInGoal();
      bool isOutOfGoal();
      bool isInBounds();
      bool isOutOfBounds();
      bool isKicked();
      bool isNotKicked();
      bool isValid();
      bool isNotValid();

  };

}

#endif // RTX_ENTITIES_BALL_H

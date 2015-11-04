/**
 * @file Robot.hpp
 * Robot class.
 *
 * @authors Ants-Oskar Mäesalu
 * @version 0.1
 */

#ifndef RTX_ENTITIES_ROBOT_H
#define RTX_ENTITIES_ROBOT_H

#include "Circle.hpp"
#include "Point2D.hpp"

#include "entityConstants.hpp"
#include "Entity.hpp"


namespace rtx {

  class Robot : public Entity, public Circle {
    public:
      Robot(const Robot&);
      Robot(const Point2D*, const double& = ROBOT_MAXIMUM_DIAMETER / 2);
      Robot(const double&, const double&,
            const double& = ROBOT_MAXIMUM_DIAMETER / 2);

    private:
      // TODO
  };

};

#endif // RTX_ENTITIES_ROBOT_H

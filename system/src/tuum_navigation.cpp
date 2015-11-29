/** @file tuum_navigation.cpp
 *  Navigation system implementation.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 */

#include "tuum_platform.hpp"
#include "tuum_navigation.hpp"
#include "tuum_visioning.hpp"
#include "tuum_localization.hpp"

namespace rtx { namespace Navigation {

  const int NAV_BALL_PICKUP_RANGE = 30;


  //TODO: position to relative position
  Transform calcBallPickupPos(Transform* bt) {
    Transform target((*bt) - NAV_BALL_PICKUP_RANGE);

    double o = bt->getPosition().getOrientation();
    target.setOrientation(o);
    return target;
  }

  Vec2i calcGoalShootPos(Transform* t) {
    /*Transform me = Localization::getTransform();
    Vec2i me_p = me.getPosition();
    Vec2i g_p = t->getPosition();

    Transform target;
    // 400, 0 (n => )
    if(me_p.distanceTo(g_p) > 360) {
      target = g_p - 300;
    } else {
      //target =
    }

    return target;*/
  }

  Ball* getNearestBall() {
    Ball* ball = nullptr;
    Transform* t = Localization::getTransform();

    double d = 1000000.0, _d;

    for(auto b : *Visioning::ballDetect.getEntities()) {
      _d = t->distanceTo(b->getTransform()->getPosition());

      if(_d < d) {
        d = _d;
        ball = b;
      }
    }

    return ball;
  }

  Goal* getOpponentGoal() {
    if(gC.getStr("Pattern.OpponentGoal") == "B")
      return Visioning::blueGoal;
    else
      return Visioning::yellowGoal;
  }

  Robot* getAlly() {
    Robot* out = nullptr;

    for(auto& r : *Visioning::robotDetect.getEntities()) {
      if(r->isAlly()) {
        out = r;
        break;
      }
    }

    return out;
  }

}}

/** @file tfb_logic.cpp
 *  Team football logic module implementation.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 2. November 2015
 */

#include "tfb_logic.hpp"

namespace rtx { namespace Logic {

  LogicState logicState;

  void setup() {
    logicState = LS_INIT;
  }

  void process() {
    /*switch(logicState) {
      case LS_INIT:

        printf("Logic initial state...\n");
        Motion::setBehaviour(Motion::MOT_CURVED);
        Motion::setTarget(Transform(0, 15, M_PI/4));

        // Motion::isTargetAchieved()
        logicState = LS_PASSIVE;
        break;
      case LS_PASSIVE:
        break;
      case LS_BALL_LOCATE:
        // Check minimal state conditions (also check if ball not in dribbler)

        //Motion::?
        // Spin to win

        if(Visioning::balls.size() > 0) {
          // Detected balls are reachable?
          logicState = LS_BALL_RETRIEVE;
        }
        break;
      case LS_BALL_RETRIEVE:
        // Check minimal state conditions

        if(hal::hw.isBallInDribbler()) {
          logicState = LS_GOAL_SCAN;
        }
        break;
      case LS_GOAL_SCAN:
        // Check minimal state conditions
        // Spin to win

        if (Visioning::yellowGoal != nullptr || Visioning::blueGoal != nullptr) {
        //if(Visioning::goals.size() > 0) { // TODO: Refactor?
          Goal* goal_ptr = nullptr;
          /*for(auto & goal : Visioning::goals) {
            if(goal.getType() = Goal::VAR_OPPOSING)  {
              goal_ptr = goal;
            }
          }*/
          /*if(goal_ptr == nullptr) break;

          logicState = LS_GOAL_SHOOT;
        }
        break;
      case LS_GOAL_SHOOT:

        // Move to possible shooting position, TODO: DESIGN MOVEMENT CONTROL

        logicState = LS_BALL_RETRIEVE;
        break;
    }*/
  }

  void printSystemState() {

  }

}}

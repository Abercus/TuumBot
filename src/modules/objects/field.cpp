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

 * Field class
 * Contributors:
 *   Ants-Oskar Mäesalu
 */

#include "field.h"

Field::Field(const Field& other):
currentGoal{other.getCurrentGoal()},
self{other.getSelf()}
{
  goals = new Goal*[2];
  if (other.getCurrentGoal() == 0) {
    goals[0] = other.getFriendlyGoal();
  } else {
    goals[1] = other.getEnemyGoal();
  }
}

Field::Field(const Goal* friendlyGoal, const Goal* enemyGoal, const RobotSelf* self):
currentGoal{0},
self{self}
{
  goals = new Goal*[2];
  goals[0] = friendlyGoal;
  goals[1] = enemyGoal;
}

void Field::swapGoals() {
  currentGoal = 1 - currentGoal;
}

int Field::getCurrentGoal() const {
  return currentGoal;
}

Goal* Field::getFriendlyGoal() const {
  return goal[currentGoal];
}

Goal* Field::getEnemyGoal() const {
  return goal[1 - currentGoal];
}

RobotSelf* Field::getSelf() const {
  return self;
}

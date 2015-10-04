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

 * 2vs2 competition program
 * Contributors:
 *   Ants-Oskar Mäesalu

 * main.cpp
 * The main function of the competition program.
 */

#include <cstdlib>
#include "../../../modules/objects/robotSelf.h"
#include "../../../modules/objects/field2vs2.h"

int main() {
	// Initialise game objects
	RobotSelf* self = new RobotSelf();
	Field2vs2* field = new Field2vs2(self);
	return EXIT_SUCCESS;
}

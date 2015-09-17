################################################################################
# Tuum                                                                         #
# Robotex 2015                                                                 #
# University of Tartu                                                          #
# Team:                                                                        #
#   Kristjan Kanarbik                                                          #
#   Meelik Kiik                                                                #
#   Ants-Oskar Mäesalu                                                         #
#   Mart Müllerbeck                                                            #
#   Kaur Viiklaid                                                              #
#   Indrek Virro                                                               #
#   Mihkel Väljaots                                                            #
################################################################################
# Makefile                                                                     #
# Contributors:                                                                #
#   Ants-Oskar Mäesalu                                                         #
# Usage instructions:                                                          #
#   TODO                                                                       #
################################################################################

# Compiler
CXX=g++

# Default compiler parameters
# -Wall 		Shows all warnings when compiling, always use this!
# -std=c++11 	Enables the C++11 standard mode
CXXFLAGS = -Wall -std=c++11

################################################################################
# Settings for the modules.                                                    #
################################################################################

# Compiler flag -Idir specifies, that there are includes in the 'dir' directory
LIB_CXXFLAGS = $(CXXFLAGS) -Iinclude

LIB_OBJS = $(LIB_COILGUN_OBJS) $(LIB_COMMUNICATION_OBJS) $(LIB_COMPUTER_VISION_OBJS) $(LIB_MATHEMATICS_OBJS) $(LIB_MOVEMENT_OBJS) $(LIB_OBJECTS_OBJS) $(LIB_TRIBBLER_OBJS)

LIBS = $(LIB_COILGUN) $(LIB_COMMUNICATION) $(LIB_COMPUTER_VISION) $(LIB_MATHEMATICS) $(LIB_MOVEMENT) $(LIB_OBJECTS) $(LIB_TRIBBLER)

# Coilgun ######################################################################

LIB_COILGUN_OBJS = ;

LIB_COILGUN = lib/coilgun.a

# Communication ################################################################

LIB_COMMUNICATION_OBJS = ;

LIB_COMMUNICATION = lib/communication.a

# Computer vision ##############################################################

LIB_COMPUTER_VISION_OBJS = ;

LIB_COMPUTER_VISION = lib/computer-vision.a

# Mathematics ##################################################################

LIB_MATHEMATICS_OBJS = obj/mathematics/circle.o obj/mathematics/line.o obj/mathematics/point2d.o obj/mathematics/rectangle.o

LIB_MATHEMATICS = lib/mathematics.a

# Movement #####################################################################

LIB_MOVEMENT_OBJS = ;

LIB_MOVEMENT = lib/movement.a

# Objects ######################################################################

LIB_OBJECTS_OBJS = obj/objects/ball.o obj/objects/field1vs1.o obj/objects/field2vs2.o obj/objects/field.o obj/objects/goal.o obj/objects/object.o obj/objects/robot.o obj/objects/robotEnemy.o obj/objects/robotFriend.o obj/objects/robotSelf.o

LIB_OBJECTS = lib/objects.a

# Tribbler #####################################################################

LIB_TRIBBLER_OBJS = ;

LIB_TRIBBLER = lib/tribbler.a

################################################################################
# Settings for the programs.                                                   #
################################################################################

PROGRAMS = $(PROGRAMS_CALIBRATION) $(PROGRAMS_COMPETITION) $(PROGRAMS_SIMULATION)

################################################################################
# Settings for the calibration programs.                                       #
################################################################################

PROGRAMS_CALIBRATION = $(PROGRAM_CALIBRATION_COLOR) $(PROGRAM_CALIBRATION_LENS) $(PROGRAM_CALIBRATION_PERSPECTIVE) $(PROGRAMS_CALIBRATION_POSITION) $(PROGRAMS_CALIBRATION_SPEED)

# Color ########################################################################

PROGRAM_CALIBRATION_COLOR_OBJS = ;

PROGRAM_CALIBRATION_COLOR = bin/calibration-color

# Lens #########################################################################

PROGRAM_CALIBRATION_LENS_OBJS = ;

PROGRAM_CALIBRATION_LENS = bin/calibration-lens

# Perspective ##################################################################

PROGRAM_CALIBRATION_PERSPECTIVE_OBJS = ;

PROGRAM_CALIBRATION_PERSPECTIVE = bin/calibration-perspective

# Position #####################################################################

PROGRAM_CALIBRATION_POSITION_OBJS = ;

PROGRAM_CALIBRATION_POSITION = bin/calibration-position

# Speed ########################################################################

PROGRAM_CALIBRATION_SPEED_OBJS = ;

PROGRAM_CALIBRATION_SPEED = bin/calibration-speed

################################################################################
# Settings for the competition programs.                                       #
################################################################################

PROGRAMS_COMPETITION = $(PROGRAM_COMPETITION_1VS1) $(PROGRAM_COMPETITION_2VS2)

# 1vs1 #########################################################################

PROGRAM_COMPETITION_1VS1_OBJS = ;

PROGRAM_COMPETITION_1VS1 = bin/competition-1vs1

# 2vs2 #########################################################################

PROGRAM_COMPETITION_2VS2_OBJS = ;

PROGRAM_COMPETITION_2VS2 = bin/competition-2vs2

################################################################################
# Settings for the simulation programs.                                        #
################################################################################

PROGRAMS_SIMULATION = $(PROGRAM_SIMULATION_1VS1) $(PROGRAM_SIMULATION_2VS2)

# 1vs1 #########################################################################

PROGRAM_SIMULATION_1VS1_OBJS = ;

PROGRAM_SIMULATION_1VS1 = bin/simulation-1vs1

# 2vs2 #########################################################################

PROGRAM_SIMULATION_2VS2_OBJS = ;

PROGRAM_SIMULATION_2VS2 = bin/simulation-2vs2

################################################################################
# Make rules.                                                                  #
################################################################################

# build - Target that builds all of the necessary libraries ####################

build:
	coilgun
	communication
	computer-vision
	mathematics
	movement
	objects
	tribbler

coilgun:
	$(LIB_COILGUN)

$(LIB_COILGUN): $(LIB_COILGUN_OBJS)
	ar cr $(LIB_COILGUN) $(LIB_COILGUN_OBJS)

# TODO: Coilgun module object compilation rules

communication:
	$(LIB_COMMUNICATION)

$(LIB_COMMUNICATION): $(LIB_COMMUNICATION_OBJS)
	ar cr $(LIB_COMMUNICATION) $(LIB_COMMUNICATION_OBJS)

# TODO: Communication module object compilation rules

computer-vision:
	$(LIB_COMPUTER_VISION)

$(LIB_COMPUTER_VISION): $(LIB_COMPUTER_VISION_OBJS)
	ar cr $(LIB_COMPUTER_VISION) $(LIB_COMPUTER_VISION_OBJS)

# TODO: Computer vision module object compilation rules

mathematics:
	$(LIB_MATHEMATICS)

$(LIB_MATHEMATICS): $(LIB_MATHEMATICS_OBJS)
	ar cr $(LIB_MATHEMATICS) $(LIB_MATHEMATICS_OBJS)

obj/mathematics/circle.o: src/mathematics/circle.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/mathematics/circle.cpp -o obj/mathematics/circle.o
obj/mathematics/line.o: src/mathematics/line.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/mathematics/line.cpp -o obj/mathematics/line.o
obj/mathematics/point2d.o: src/mathematics/point2d.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/mathematics/point2d.cpp -o obj/mathematics/point2d.o
obj/mathematics/rectangle.o: src/mathematics/rectangle.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/mathematics/rectangle.cpp -o obj/mathematics/rectangle.o

movement:
	$(LIB_MOVEMENT)

$(LIB_MOVEMENT): $(LIB_MOVEMENT_OBJS)
	ar cr $(LIB_MOVEMENT) $(LIB_MOVEMENT_OBJS)

# TODO: Movement module object compilation rules

objects:
	$(LIB_OBJECTS)

$(LIB_OBJECTS): $(LIB_OBJECTS_OBJS)
	ar cr $(LIB_OBJECTS) $(LIB_OBJECTS_OBJS)

obj/objects/ball.o: src/objects/ball.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/objects/ball.cpp -o obj/objects/ball.o
obj/objects/field1vs1.o: src/objects/field1vs1.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/objects/field1vs1.cpp -o obj/objects/field1vs1.o
obj/objects/field2vs2.o: src/objects/field2vs2.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/objects/field2vs2.cpp -o obj/objects/field2vs2.o
obj/objects/field.o: src/objects/field.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/objects/field.cpp -o obj/objects/field.o
obj/objects/goal.o: src/objects/goal.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/objects/goal.cpp -o obj/objects/goal.o
obj/objects/object.o: src/objects/object.pp
	$(CXX) $(LIB_CXXFLAGS) -c src/objects/object.cpp -o obj/objects/object.o
obj/objects/robot.o: src/objects/robot.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/objects/robot.cpp -o obj/objects/robot.o
obj/objects/robotEnemy.o: src/objects/robotEnemy.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/objects/robotEnemy.cpp -o obj/objects/robotEnemy.o
obj/objects/robotFriend.o: src/objects/robotFriend.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/objects/robotFriend.cpp -o obj/objects/robotFriend.o
obj/objects/robotSelf.o: src/objects/robotSelf.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/objects/robotSelf.cpp -o obj/objects/robotSelf.o

tribbler:
	$(LIB_TRIBBLER)

$(LIB_TRIBBLER): $(LIB_TRIBBLER_OBJS)
	ar cr $(LIB_TRIBBLER) $(LIB_TRIBBLER_OBJS)

# TODO: Tribbler module object compilation rules

# calibration - Target that builds only the calibration programs ###############

calibration:
	calibration-color
	calibration-lens
	calibration-perspective
	calibration-position
	calibration-speed

calibration-color: ;
	# TODO

calibration-lens: ;
	# TODO

calibration-perspective: ;
	# TODO

calibration-position: ;
	# TODO

calibration-speed: ;
	# TODO

# competition - Target that builds only the competition programs ###############

competition:
	competition-1vs1
	competition-2vs2

competition-1vs1: ;
	# TODO

competition-2vs2: ;
	# TODO

# simulation - Target that builds only the simulation programs #################

simulation:
	simulation-1vs1
	simulation-2vs2

simulation-1vs1: ;
	# TODO

simulation-2vs2: ;
	# TODO

# all - Target that builds all of the executables ##############################

all:
	calibration
	competition
	simulation

# clean - Target that cleans all of the compiled files #########################

clean:
	rm -f $(LIB_OBJS)
	rm -f $(LIBS)
	# TODO

# test - Target that builds the test application ###############################

test: ;
	# TODO

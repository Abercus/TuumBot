/** @file tuum_vision.cpp
 *  Vision system implementation.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 4 December 2015
 */

#include <algorithm>
#include <fstream>
#include <iostream> // TODO: Remove
#include <sstream>
#include <cmath>

#include "Perspective.hpp"

#include "tuum_visioning.hpp"
#include "tuum_localization.hpp"
#include "mathematicalConstants.hpp"

using namespace rtx;

namespace rtx { namespace Visioning {

  std::vector<std::string> filters;

  Timer debugTimer;

  FeatureSet features;

  EDS<Ball> ballDetect;
  BallSet balls; // Healthy ball entities vs new/decaying ball entities?
  BallSet ballsBuffer; // Unused

  Goal *yellowGoal;
  Goal *yellowGoalBuffer;
  Goal *blueGoal;
  Goal *blueGoalBuffer;

  EDS<Robot> robotDetect;
  RobotSet robots;
  RobotSet robotsBuffer; // Unused

  bool editingBalls = false; // Unused
  bool editingGoals = false;
  bool editingRobots = false; // Unused

  void setup() {
    Camera *frontCamera = hal::hw.getFrontCamera();
    Camera *backCamera = hal::hw.getBackCamera();

    readFilterFromFile("../data/colors/1.txt");
    readFilterFromFile("../data/colors/2.txt");

    Vision::setup();

    debugTimer.setPeriod(1000);
    debugTimer.start();

    printf("\033[1;32m");
    printf("[Visioning::setup()]Ready.");
    printf("\033[0m\n");
  }

  void process() {
    if (filters.size() == 0) {
      std::cout << "Process: Filters are empty" << std::endl;
      return;
    } else {
      for (std::vector<std::string>::iterator filter = filters.begin(); filter != filters.end(); ++filter) {
        if (filter->size() == 0) {
          std::cout << "Process: A filter is empty" << std::endl;
        }
      }
    }

    Camera *frontCamera = hal::hw.getFrontCamera();
    Camera *backCamera = hal::hw.getBackCamera(); // TODO: Use

    Frame frontFrame, backFrame;
    if (frontCamera)
      frontFrame = frontCamera->getFrame();
    //if (backCamera)
    //  backFrame = backCamera->getFrame();

    if (frontCamera)
      Vision::process(frontFrame, filters, 0);
    if (backCamera)
      Vision::process(frontFrame, filters, 1);

    if (frontCamera) {
      ballDetection(frontFrame);
      goalDetection(frontFrame);
      robotDetection(frontFrame);
    }

    // TODO: Add back camera frame processing
  }

  void processCheckerboard() {
    if (filters.size() == 0) {
      std::cout << "Process: Filters are empty" << std::endl;
      return;
    } else {
      for (std::vector<std::string>::iterator filter = filters.begin(); filter != filters.end(); ++filter) {
        if (filter->size() == 0) {
          std::cout << "Process: A filter is empty" << std::endl;
        }
      }
    }

    Camera *frontCamera = hal::hw.getFrontCamera();
    Camera *backCamera = hal::hw.getBackCamera(); // TODO: Use

    Frame frontFrame, backFrame;
    if (frontCamera)
      frontFrame = frontCamera->getFrame();
    if (backCamera)
      backFrame = backCamera->getFrame();

    if (frontCamera)
      Vision::processCheckerboard(frontFrame, filters, 0);
    if (backCamera)
      Vision::processCheckerboard(backFrame, filters, 1);

    // TODO: Add back camera frame processing
  }

  void readFilterFromFile(const std::string &fileName) {
    std::ifstream inputFile(fileName);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    filters.push_back(buffer.str());
    inputFile.close();
  }

  // Unused
  void translateBallsBuffer() {
    editingBalls = true;

    balls.clear();
    balls = ballsBuffer;
    ballsBuffer.clear();

    editingBalls = false;
  }

  void translateGoalsBuffer() {
    editingGoals = true;

    const int mn_h = -5;
    const int mx_h = 5;

    Goal* g = blueGoal;
    Goal* new_g = blueGoalBuffer;

    if (blueGoal != nullptr) {

      if (blueGoalBuffer != nullptr) {
        blueGoal->update(*blueGoalBuffer->getTransform());
        blueGoal->update(*blueGoalBuffer->getBlob());
      } else {
        blueGoal->update();
      }

      if (blueGoal->getHealth() <= mn_h) {
        delete blueGoal;
      blueGoal = nullptr;
      }
    } else if (blueGoalBuffer != nullptr) {
      blueGoal = new Goal(*blueGoalBuffer);
    }

    if (yellowGoal != nullptr) {
      if (yellowGoalBuffer != nullptr) {
        yellowGoal->update(*yellowGoalBuffer->getTransform());
        yellowGoal->update(*yellowGoalBuffer->getBlob());
      } else {
        yellowGoal->update();
      }

      if(yellowGoal->getHealth() <= mn_h) {
        delete yellowGoal;
        yellowGoal = nullptr;
      }
    } else if(yellowGoalBuffer != nullptr) {
      yellowGoal = new Goal(*yellowGoalBuffer);
    }

    // TODO: Remove casting to null pointers when localisation is working
    blueGoalBuffer = nullptr;
    yellowGoalBuffer = nullptr;

    editingGoals = false;
  }

  // Unused
  void translateRobotsBuffer() {
    editingRobots = true;

    robots.clear();
    robots = robotsBuffer;
    robotsBuffer.clear();

    editingRobots = false;
  }

  double stateProbability(Transform* t1, Transform* t2) {
    const double A = 125.0;
    double px = A*gauss_prob2(t1->getX(), 120, t2->getX());
    double py = A*gauss_prob2(t1->getY(), 120, t2->getY());
    return 2*px*py / (px+py);
  }

  void ballDetection(const Frame &frame) {

    Vision::BlobSet blobs = Vision::getBlobs();

    BallSet n_balls;

    /*
    std::stringstream dbg;
    dbg << "Ball detect debug:" << std::endl;
    bool dbg_available = false;
    */

    for(unsigned int i = 0; i < blobs.size(); ++i) {

      Color color = blobs[i]->getColor();
      double density = blobs[i]->getDensity();
      unsigned int boxArea = blobs[i]->getBoxArea();
      double ratio = blobs[i]->getBoxRatio();

      // STEP 1: Filter out invalid blobs
      if(color != BALL) continue;
      if(boxArea > CAMERA_WIDTH * CAMERA_HEIGHT) continue;
      if(density > 1.0) continue;
      if(boxArea < 4 * 4) continue;
      if(fabs(1 - ratio) > 0.3) continue;
      /* && density > 0.6*/

      //std::cout << "Dim: " << blobs[i]->getDensity() << " " << blobs[i]->getBoxArea() << std::endl;

      // STEP 2: Calculate relative position
      std::pair<double, double> position = Vision::Perspective::virtualToReal(blobs[i]->getPosition(), blobs[i]->getCameraID);
      double distance = sqrt(position.second * position.second + position.first * position.first);
      double angle = -atan2(position.first, position.second);
      // Debug: std::cout << "Ball: " << distance << " " << angle << std::endl;
      //unsigned int distance = CAMERA_HEIGHT - point->getY();
      //double angle = (1 - point->getX() / (CAMERA_WIDTH / 2.0)) * 20 * PI / 180;

      /*
      dbg << "<Blob d=" << distance << ", a=" << angle
	        << ", S=" << boxArea << ", ro=" << density
	        << std::endl;
      dbg_available = true;
      */

      // STEP 3: Create ball instance with absolute position
      //std::cout << "New ball: d=" << distance << ", a=" << angle << ", r=" << fabs(1.0 - ratio) << std::endl;
      n_balls.push_back(new Ball(Localization::toAbsoluteTransform(distance, angle), blobs[i], false));
    }

    /*
    if(dbg_available) {
      dbg << "Ball detect debug end" << std::endl << std::endl;
      std::cout << dbg.str();
    }
    */

    // STEP 4: Unite detected balls with balls from last frame or create new balls
    double p, _p, p_ix;
    Ball* n_ball_ptr;
    BallSet* ball_set_ptr;
    for(int ix = 0; ix < n_balls.size(); ix++) {
      ballDetect.processProbableEntity(n_balls[ix]);
    }

    // STEP 5: Entity vectors updates - remove decayed balls and make healthy detectable
    ballDetect.update();

    if(debugTimer.isTime()) {
      /*std::cout << "[Visioning]Balls: " << ballDetect.getEntities()->size()
	        << ". Unconfirmed balls: " << ballDetect.getTmpEntities()->size()
		<< std::endl;
      */

      /*for(auto& b : *(ballDetect.getEntities())) {
	Transform* t = b->getTransform();
        std::cout << "<Ball hp=" << b->getHealth() << ", x=" << t->getX() << ", y=" << t->getY() << ">" << std::endl;
      }*/

      debugTimer.start();
    }
  }

  void goalDetection(const Frame &frame) {
    // TODO: Remove casting to null pointers when localisation is working
    blueGoalBuffer = nullptr;
    yellowGoalBuffer = nullptr;

    Vision::BlobSet blobs = Vision::getBlobs();

    unsigned int largestYellowArea = 0, largestBlueArea = 0;

    for (unsigned int i = 0; i < blobs.size(); ++i) {
      Color color = blobs[i]->getColor();
      double density = blobs[i]->getDensity();
      unsigned int boxArea = blobs[i]->getBoxArea();
      //double ratio = blobs[i]->getBoxRatio();

      // Filter out invalid blobs
      if (color != BLUE_GOAL && color != YELLOW_GOAL) continue;
      if (boxArea > CAMERA_WIDTH * CAMERA_HEIGHT) continue;
      if (density > 1.0) continue;
      if(boxArea < 20 * 20) continue; // TODO: Calibrate with field tests
      //if(fabs(1 - ratio) > 0.3) continue;
      /* && density > 0.6*/

      // Relative position
      std::pair<double, double> position = Vision::Perspective::virtualToReal(blobs[i]->getPosition(), blobs[i]->getCameraID);
      double distance = sqrt(position.second * position.second + position.first * position.first);
      double angle = -atan2(position.first, position.second);
      // std::cout << "Goal: " << distance << " " << angle << std::endl;
      //unsigned int distance = CAMERA_HEIGHT - point->getY();
      //double angle = (1 - point->getX() / (CAMERA_WIDTH / 2.0)) * 20 * PI / 180;
      // TODO: Remove duplicate code
      if (color == BLUE_GOAL) {
        if (boxArea > largestBlueArea) {
          largestBlueArea = boxArea;
          //if (blueGoalBuffer == nullptr) {
          blueGoalBuffer = new Goal(Localization::toAbsoluteTransform(distance, angle), blobs[i]);
          /*} else {
            blueGoalBuffer->setDistance(distance); // TODO: Compare with previous values as in ball detection
            blueGoalBuffer->setAngle(angle); // TODO: Compare with previous values as in ball detection
          }*/
        }
      } else {
        if (boxArea > largestYellowArea) {
          largestYellowArea = boxArea;
          //if (yellowGoalBuffer == nullptr) {
          yellowGoalBuffer = new Goal(Localization::toAbsoluteTransform(distance, angle), blobs[i]);
          /*} else {
            yellowGoalBuffer->setDistance(distance); // TODO: Compare with previous values as in ball detection
            yellowGoalBuffer->setAngle(angle); // TODO: Compare with previous values as in ball detection
          }*/
        }
      }

    }

    translateGoalsBuffer();
  }

  void robotDetection(const Frame &frame) {

    Vision::BlobSet blobs = Vision::getBlobs();

    RobotSet n_robots;

    for(unsigned int i = 0; i < blobs.size(); ++i) {
      Color color = blobs[i]->getColor();
      double density = blobs[i]->getDensity();
      unsigned int boxArea = blobs[i]->getBoxArea();
      //double ratio = blobs[i]->getBoxRatio();

      // STEP 1: Filter out invalid blobs
      if (color != ROBOT_YELLOW_BLUE && color != ROBOT_BLUE_YELLOW) continue;
      if (boxArea > CAMERA_WIDTH * CAMERA_HEIGHT) continue;
      if (density > 1.0) continue;
      //if(boxArea < 8 * 3) continue; // TODO: Calibrate with field tests
      //if(fabs(1 - ratio) > 0.3) continue;
      /* && density > 0.6*/

      // STEP 2: Calculate relative position
      std::pair<double, double> position = Vision::Perspective::virtualToReal(blobs[i]->getPosition(), blobs[i]->getCameraID);
      double distance = sqrt(position.second * position.second + position.first * position.first);
      double angle = -atan2(position.first, position.second);
      // std::cout << "Robot: " << distance << " " << angle << std::endl;
      //unsigned int distance = CAMERA_HEIGHT - point->getY();
      //double angle = (1 - point->getX() / (CAMERA_WIDTH / 2.0)) * 20 * PI / 180;

      // STEP 3: Create robot instance with absolute position
      n_robots.push_back(new Robot(Localization::toAbsoluteTransform(distance, angle), blobs[i]));
    }

    // STEP 4: Unite detected robots with robots from last frame or create new robots
    double p, _p, p_ix;
    Robot* n_robot_ptr;
    RobotSet* robot_set_ptr;
    for (int ix = 0; ix < n_robots.size(); ix++) {
      p = 0.0;
      n_robot_ptr = n_robots[ix];

      // STEP 4.1: Calculate existing entity probability
      robot_set_ptr = &(robotDetect.objs);
      for (int jx = 0; jx < robotDetect.objs.size(); jx++) {
        _p = stateProbability((*robot_set_ptr)[jx]->getTransform(), n_robot_ptr->getTransform());
        if (_p > p) {
          p = _p;
          p_ix = jx;
        }
      }

      for (int jx = 0; jx < robotDetect.tmp_objs.size(); jx++) {
        _p = stateProbability(robotDetect.tmp_objs[jx]->getTransform(), n_robot_ptr->getTransform());
        if (_p > p) {
          p = _p;
          p_ix = jx;
          if(robot_set_ptr != &(robotDetect.tmp_objs)) robot_set_ptr = &(robotDetect.tmp_objs);
        }
      }

      // STEP 4.2: Create or update entities
      if (p < 0.01) {
        robotDetect.tmp_objs.push_back(new Robot(*n_robot_ptr));
      } else {
        (*robot_set_ptr)[p_ix]->update(*n_robot_ptr->getTransform());
        (*robot_set_ptr)[p_ix]->update(*n_robot_ptr->getBlob());
      }
    }

    // STEP 5: Entity vectors updates - remove decayed balls and make healthy detectable
    robotDetect.update();
  }

}}

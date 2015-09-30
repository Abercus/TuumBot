/**
  Tuum
  Robotex 2015
  University of Tartu
  Team:
    Kristjan Kanarbik
    Meelik Kiik
    Ants-Oskar Mäesalu
    Mart Müllerbeck
    Kaur Viiklaid
    Indrek Virro
    Mihkel Väljaots

  Camera class
    Class for communication with the robot's cameras, based on the V4L2 API.
    The video capture example provided with the V4L2 API has been used as a
    model for the class.

  Contributors:
    Ants-Oskar Mäesalu

  Copyright (c) 2015 Ants-Oskar Mäesalu
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <string>

#include "constants.h"    // Camera constants

class Camera {

public:

  /**
    Camera constructor. Receives the camera device location and the preferred
    resolution dimensions as parameters.
    Opens and initialises the device, and starts capturing.
  */
  Camera(const std::string& = CAMERA_DEVICE, const int& = CAMERA_WIDTH,
         const int& = CAMERA_HEIGHT);

  /**
    Camera destructor.
    Stops capturing, uninitialises and closes the device.
  */
  ~Camera();

  /**
    Returns the camera device's path.
  */
  std::string getDevice() const;

  /**
    Returns the camera resolution's width.
  */
  int getWidth() const;

  /**
    Returns the camera resolution's height.
  */
  int getHeight() const;

private:

  /**
    The camera device's path. The default value for this variable is described
    in the camera constants file. The value actually used in the program can be
    set upon class initialisation.
    In Linux operating systems, this is usually /dev/videoN, where N is the
    video device's number.
  */
  std::string device;

  /**
    The camera resolution's width. The default value for this variable is
    described in the camera constants file. The value actually used in the
    program can be set upon class initialisation.
  */
  int width;

  /**
    The camera resolution's height. The default value for this variable is
    described in the camera constants file. The value actually used in the
    program can be set upon class initialisation.
  */
  int height;

  /**
    The camera device's file descriptor. This specific value is set upon opening
    the device and is used in I/O operations performed on the device, and upon
    closing the device.
  */
  int fileDescriptor;

  /**
    Opens the camera device. Establishes a connection between a file and a file
    descriptor. Creates an open file description that refers to a file and a
    file descriptor that refers to that open file description. The file
    descriptor is used by other I/O functions to refer to that file.
    The file descriptor is set to the lowest file descriptor not currently open
    for the current process. The open file description is new, and therefore the
    file descriptor shall not share it with any other process in the system.
    Throws a runtime error if the device cannot be identified, if it is not an
    appropriate device, or if it cannot be opened.
  */
  void openDevice();

  /**
    Closes the camera device. All I/O progress is terminated and resources
    associated with the file descriptor are freed. However, data format
    parameters, current input or output, control values or other properties
    remain unchanged.
    Throws a runtime error if the device cannot be closed. This can only happen
    if the file descriptor used upon closing the device is not a valid open file
    descriptor of the device.
  */
  void closeDevice();

  /**
    Initialises the camera device.
    Checks the camera device's V4L2 capabilites, cropping capabilities, [...] TODO
  */
  void initialiseDevice();

  /**
    // TODO
  */
  void uninitialiseDevice();

  /**
    // TODO
  */
  void startCapturing();

  /**
    // TODO
  */
  void stopCapturing();

  /**
    Checks if the camera has the necessary capabilities compatible with V4L2 to
    be used for this application.
    Queries the device capabilities and checks if they are compatible with the
    V4L2 specification. Checks if the device supports the Video Capture
    interface and the streaming I/O method. If any of these capabilities are not
    apparent in the device, the method throws a runtime error.
  */
  void checkV4L2Capabilities();

  /**
    Checks if the camera has cropping capabilites.
  */
  void checkCroppingCapabilites();

  /**
    Initialises the camera device video format.
    Sets the width and height of the image to the values passed to the class
    constructor, sets the pixel format to YUYV and interlaces the video.
    // TODO: Deinterlace the video if needed.
  */
  void initialiseFormat();

};

#endif // CAMERA_H

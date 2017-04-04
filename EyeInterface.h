#ifndef _EyeInterface_
#define _EyeInterface_

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>
#include <string>

#include "OpenCV/findEyeCenter.h"
#include "OpenCV/findEyeCorner.h"
#include "OpenCV/constants.h"

/** Represents an Eye */
class EyeInterface {
public:
	int x; /**< x-coordinate of the eye */
	int y; /**< y-coordinate of the eye */
	CvCapture* capture; /**< pointer to the webcam feed */
  	cv::Mat frame;  /**< matrix used to calculate face position */
  	int counter; /**< used to limit the rate of calculations so as not to slow down the game  */
  	int blinkCount; /**< increments each time a blink is detected */

  	/** Initialize an eye */
	EyeInterface();

	/** Destroy an eye */
	~EyeInterface();

	/** Calculates gaze position */
	void update();

	/** Calculates simulated distance to user's face and sets a value to distance accordingly */
	void findEyes(cv::Mat frame_gray, cv::Rect face);

	/** Finds the face position */
	void detectAndDisplay(cv::Mat frame );
};

#endif // _EyeInterface_
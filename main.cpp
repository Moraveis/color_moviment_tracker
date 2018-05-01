//COMPILE COMMAND : sudo g++ detectorMovimentoCores_v1.1.cpp -o detector `pkg-config --cflags --libs opencv`

#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>

using namespace std;
using namespace cv;

// setting variables
const static int SENSITIVITY_VALUE = 20; // sensibilidade no movimento
const static int BLUR_SIZE = 20; // smooth area

// auxiliars variables
bool trackingEnabled = true;
int theObject[2] = {0,0};
Rect objectBoundingRectangle = Rect(0,0,0,0);

// function's header
void searchForMovement(Mat thresholdImage, Mat &cameraFeed);
void showImgContours(Mat &threshedimg,Mat &original);
string intToString(int number);

int main(){
  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened())  // check if we succeeded
    return -1;

  // input stream of captured frames
  Mat frameMotion1, frameMotion2;
  //
  Mat smoothImage;
  // grayscale frames
  Mat grayMotion1, grayMotion2;
  // save the difference between the two frames form absdiff()
  Mat differenceImage;
  // highlight edge pixels
  Mat thresholdImage;

  while(1){
    cap >> frameMotion1; // get a new frame from camera
    //cvtColor(frameMotion1, grayMotion1, CV_BGR2GRAY);

    //bilateralFilter ( src, dst, d(diameter of each pixel neighborhood), sigmaColor, sigmaSpace );
    bilateralFilter(frameMotion1, smoothImage,20,100,100);
    namedWindow("bilateralFilter",CV_WINDOW_NORMAL);
    imshow("bilateralFilter", smoothImage);
    resizeWindow("bilateralFilter",620,500);

    cvtColor(smoothImage, grayMotion1, CV_BGR2GRAY);

    cap >> frameMotion2;
    cvtColor(frameMotion2, grayMotion2, CV_BGR2GRAY);

    //namedWindow(const string& winname, int flags=WINDOW_AUTOSIZE )
    namedWindow("normalFrame",CV_WINDOW_NORMAL);
    //imshow(const string& winname, InputArray mat)
    imshow("normalFrame", frameMotion1);
    //ResizeWindow(name, width, height)
    resizeWindow("normalFrame",618,500);

    //imshow("gray normal frame", grayMotion1);
    namedWindow("grayFrame",CV_WINDOW_NORMAL);
    imshow("grayFrame", grayMotion1);
    resizeWindow("grayFrame",618,500);

    absdiff(grayMotion1, grayMotion2, differenceImage);

    namedWindow("Difference",CV_WINDOW_NORMAL);
    imshow("Difference", differenceImage);
    resizeWindow("Difference",620,500);

    threshold(differenceImage,thresholdImage,SENSITIVITY_VALUE,255,THRESH_BINARY);

    blur(thresholdImage,differenceImage,cv::Size(BLUR_SIZE, BLUR_SIZE));
    threshold(differenceImage,thresholdImage,SENSITIVITY_VALUE,255,THRESH_BINARY);

    namedWindow("Threshold",CV_WINDOW_NORMAL);
    imshow("Threshold", thresholdImage);
    resizeWindow("Threshold",620,500);

    if(trackingEnabled){
      searchForMovement(thresholdImage,frameMotion1);
    }

    namedWindow("Resultado",CV_WINDOW_NORMAL);
    imshow("Resultado", frameMotion1);
    resizeWindow("Resultado",620,500);
    if(waitKey(30) >= 0) break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}

string intToString(int number){
	//this function has a number input and string output
	std::stringstream ss;
	ss << number;
	return ss.str();
}

void searchForMovement(Mat thresholdImage, Mat &cameraFeed){
  //notice how we use the '&' operator for the cameraFeed. This is because we wish
	//to take the values passed into the function and manipulate them, rather than just working with a copy.
	//eg. we draw to the cameraFeed in this function which is then displayed in the main() function.
	bool objectDetected=false;
	Mat temp;
	thresholdImage.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	//findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );// retrieves all contours
	findContours(temp,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );// retrieves external contours

	//if contours vector is not empty, we have found some objects
	if(contours.size()>0)objectDetected=true;
	else objectDetected = false;

	if(objectDetected){
    Mat hsvframe, rangeframe;

    //flip(cameraFeed, cameraFeed, 180);
		cvtColor(cameraFeed, hsvframe, COLOR_BGR2HSV);

    //inRange(hsvframe, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), rangeframe);
    //inRange(hsvframe, Scalar(0, 0, 0), Scalar(175, 134, 255), rangeframe);
    //inRange(hsvframe, Scalar(0, 0, 0), Scalar(180, 255, 30), rangeframe); //black
    //inRange(hsvframe, Scalar(0, 100, 100), Scalar(10, 255, 255), rangeframe); orange
    inRange(hsvframe, Scalar(160, 100, 100), Scalar(179, 255, 255), rangeframe); //red

    //the largest contour is found at the end of the contours vector
		//we will simply assume that the biggest contour is the object we are looking for.
		vector< vector<Point> > largestContourVec;
		largestContourVec.push_back(contours.at(contours.size()-1));

    //make a bounding rectangle around the largest contour then find its centroid
		//this will be the object's final estimated position.
		objectBoundingRectangle = boundingRect(largestContourVec.at(0));
		int xpos = objectBoundingRectangle.x+objectBoundingRectangle.width/2;
		int ypos = objectBoundingRectangle.y+objectBoundingRectangle.height/2;

		//update the objects positions by changing the 'theObject' array values
		theObject[0] = xpos , theObject[1] = ypos;

    //make some temp x and y variables so we dont have to type out so much
  	int x = theObject[0];
  	int y = theObject[1];

    //draw some crosshairs on the object
  	circle(cameraFeed,Point(x,y),20,Scalar(0,255,0),2);
  	line(cameraFeed,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
  	line(cameraFeed,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
  	line(cameraFeed,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
  	line(cameraFeed,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
    putText(cameraFeed,"Tracking object at (" + intToString(x)+","+intToString(y)+")",Point(x,y),1,1,Scalar(255,0,0),2);

    namedWindow("Movement",CV_WINDOW_NORMAL);
    imshow("Movement", cameraFeed);
    resizeWindow("Movement",620,500);

    showImgContours(rangeframe, cameraFeed);
	}
}

void showImgContours(Mat &threshedimg, Mat &original)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	int largest_area = 0;
	int largest_contour_index = 0;

	findContours(threshedimg, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

	//this will find largest contour
	for (int i = 0; i< contours.size(); i++) // iterate through each contour.
	{
		double a = contourArea(contours[i], false);  //  Find the area of contour
		if (a>largest_area)
		{
			largest_area = a;
			largest_contour_index = i;                //Store the index of largest contour
		}
	}

	//search for largest contour has end
	if (contours.size() > 0)
	{
		drawContours(original, contours,largest_contour_index, CV_RGB(0, 0, 255), 2, 8, hierarchy);

		//if want to show all contours use below one
		//drawContours(original,contours,-1, CV_RGB(0, 255, 0), 2, 8, hierarchy);
	}
  //imshow("teste", original);
}

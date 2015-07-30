#include <iostream>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "opencv2\highgui\highgui.hpp"
#include "imgproc.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;
using namespace std;

int main() {
	VideoCapture capture(0);
	if (!capture.isOpened()) {
		cout << "Error";
		return -1;
	}

	vector<Point2f> corners;
	int maxCorners = 20;
	double qualitylevel = 0.01;
	double minDist = 20.;
	cv::Mat mask;
	int blockSize = 3;
	bool useHarris = false;
	double k = 0.04;
	Mat Frame, gray;
	while (1) {
		
		capture >> Frame;
		waitKey(10);
		cvtColor(Frame, gray, CV_BGR2GRAY);
		cv::equalizeHist(gray, gray);
	
		gray.convertTo(gray, CV_8UC1);
	
		goodFeaturesToTrack(gray, corners, maxCorners, qualitylevel, minDist, mask, blockSize, useHarris, k);

		for (size_t i = 0; i < corners.size(); i++) {
			circle(gray, corners[i], 10, Scalar(255.), -1);
		}

		imshow("frame", gray);
		if (waitKey(30) >= 0) break;
		
	}
	
	return 0;
}
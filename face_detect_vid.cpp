#include <stdio.h>
#include <math.h>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main() {
	CascadeClassifier face_cascade, eye_cascade;
	//check if loading worked
	if (!face_cascade.load("C:\\Opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml")) {
		printf("Error loading frontal haar");
		return 1;
	}

	if (!eye_cascade.load("C:\\Opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml")) {
		printf("Error loading eye");
		return 1;
	}
	/*
	VideoCapture capture(0); //webcam
	if (!capture.isOpened()) {
		printf("error opening camera");
		return 1;
	}
	*/
	cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCreateFileCapture("H:\\Bakatöö\\raw vid\\done\\minansm.mp4");
	IplImage* frame;

	Mat cap_img, gray_img;
	vector<Rect> faces, eyes;
	while (1) {
		frame = cvQueryFrame(capture);
		if (!frame) break;
		Mat cap_img = cvarrToMat(frame);//iplimage to mat
		//capture >> cap_img;//will grab frame from screen/cam
		waitKey(10);
		cvtColor(cap_img, gray_img, CV_BGR2GRAY);//to grayscale
		cv::equalizeHist(gray_img, gray_img);//equalize histogram?
		face_cascade.detectMultiScale(gray_img, faces, 1.1, 10, CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, CvSize(0, 0), cvSize(300, 300));
		for (int i = 0; i < faces.size(); i++) {
			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point pt2(faces[i].x, faces[i].y); //draw rect on face
			Mat faceROI = gray_img(faces[i]);//region of interest - face
			eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
			for (size_t j = 0; j < eyes.size(); j++) {
				Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
				int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);//draw circle
				circle(cap_img, center, radius, Scalar(255, 0, 0), 2, 8, 0);
			}
			rectangle(cap_img, pt1, pt2, cvScalar(0, 255, 0), 2, 8, 0);//2==border
		}
	
		imshow("result", cap_img);
		waitKey(30);
		char c = waitKey(3);
		if (c == 27) break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Example2");
	return 0;
}
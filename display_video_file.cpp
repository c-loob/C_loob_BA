#include <opencv2\highgui\highgui.hpp>

int main() {
	cvNamedWindow("video disp", CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCreateFileCapture("H:\\video\\ISE\\emaj�e suva\\emaj�e suvatest1.mov");
	IplImage* frame;
	while (1) {
		frame = cvQueryFrame(capture);
		if (!frame) break;
		cvShowImage("video disp", frame);
		char c = cvWaitKey(20);
		if (c == 27) break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Example2");
	return 0;
}
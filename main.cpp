
#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <highgui/highgui_c.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat src = imread("C:/Users/vector/Desktop/pic/female/000001.jpg");
	imshow("123", src);
	waitKey(10000);
	destroyAllWindows();
	return 0;
}
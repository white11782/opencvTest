#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("E:\\研究生资料\\老婆\\相册\\145kb.jpg");
	if (!srcImg.data)
		return -1;
	Mat srcGray;
	cvtColor(srcImg, srcGray, COLOR_BGR2GRAY);
	Mat srcBinary;
	threshold(srcGray, srcBinary, 160, 255, THRESH_BINARY);
	Mat dstImg;
	distanceTransform(srcBinary, dstImg, DIST_L2,
		DIST_MASK_PRECISE);
	normalize(dstImg, dstImg, 0, 1., NORM_MINMAX);
	imshow("scrBinary", srcBinary);
	imshow("dstImg", dstImg);
	waitKey(0);
	return 0;
}
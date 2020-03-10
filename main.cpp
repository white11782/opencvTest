#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
float calcEuclideanDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(float((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}
int calcChessboardDistance(int x1, int y1, int x2, int y2)
{
	return max(abs(x1 - x2), abs(y1 - y2));
}
int calcBlockDistance(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}
void distanceTrans(Mat& srcImg, Mat& resultImg)
{
	CV_Assert(srcImg.data != NULL);
	Mat srcGray, srcBinary;
	cvtColor(srcImg, srcGray, COLOR_RGB2GRAY);
	threshold(srcGray, srcBinary, 100, 255, THRESH_BINARY);
	imshow("srcBinary", srcBinary);
	int rows = srcBinary.rows;
	int cols = srcBinary.cols;
	uchar* pDataOne;
	uchar* pDataTwo;
	float disPara = 0;
	float fDisMin = 0;
	for (int i = 0; i < rows-1; i++)
	{
		pDataOne = srcBinary.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			pDataTwo = srcBinary.ptr<uchar>(i - 1);
			disPara = calcEuclideanDistance(i, j, i - 1, j - 1);
			fDisMin = min((float)pDataOne[j],
				disPara + pDataTwo[j - 1]);
			disPara = calcEuclideanDistance(i, j, i - 1, j);
			fDisMin = min(fDisMin,
				disPara + pDataTwo[j]);
			pDataTwo = srcBinary.ptr<uchar>(i);
			disPara = calcEuclideanDistance(i, j, i, j - 1);
			fDisMin = min(fDisMin,
				disPara + pDataTwo[j - 1]);
			pDataTwo = srcBinary.ptr<uchar>(i + 1);
			disPara - calcEuclideanDistance(i, j, i + 1, j - 1);
			fDisMin = min(fDisMin,
				disPara + pDataTwo[j - 1]);
			pDataOne[j] = (uchar)cvRound(fDisMin);
		}
	}
	for (int i = rows-2; i > 0; i--)
	{
		pDataOne = srcBinary.ptr<uchar>(i);
		for (int j = cols-1; j >=0; j--)
		{
			pDataTwo = srcBinary.ptr<uchar>(i + 1);
			disPara = calcEuclideanDistance(i, j, i + 1, j);
			fDisMin = min((float)pDataOne[j],
				disPara + pDataTwo[j]);
			disPara = calcEuclideanDistance(i, j, i + 1, j + 1);
			fDisMin = min(fDisMin,
				disPara + pDataTwo[j + 1]);
			pDataTwo = srcBinary.ptr<uchar>(i);
			disPara = calcEuclideanDistance(i, j, i, j + 1);
			fDisMin = min(fDisMin,
				disPara + pDataTwo[j + 1]);
			pDataTwo = srcBinary.ptr<uchar>(i - 1);
			disPara = calcEuclideanDistance(i, j, i - 1, j + 1);
			fDisMin = min(fDisMin,
				disPara + pDataTwo[j + 1]);
			pDataOne[j] = (uchar)cvRound(fDisMin);
		}
	}
	resultImg = srcBinary.clone();
}
int main()
{
	Mat srcImg = imread("E:\\研究生资料\\老婆\\相册\\145kb.jpg");
	if (!srcImg.data)
		return -1;
	Mat resultImg;
	distanceTrans(srcImg, resultImg);
	imshow("resultImg", resultImg);
	waitKey(0);
	return 0;
}
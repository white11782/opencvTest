#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat gammaTransform(Mat& srcImg, float kFractor)
{
	unsigned char LUT[256];
	for (int i = 0; i < 256; i++)
	{
		LUT[i] = saturate_cast<uchar>(pow((float)(i / 255.0), kFractor) * 255.0f);
	}
	Mat resultImg = srcImg.clone();
	if (srcImg.channels() == 1)
	{
		MatIterator_<uchar>iterator =
			resultImg.begin<uchar>();
		MatIterator_<uchar>iteratorEnd =
			resultImg.end<uchar>();
		for (; iterator!= iteratorEnd; iterator++)
			*iterator = LUT[(*iterator)];
	}
	else
	{
		MatIterator_<Vec3b>iterator =
			resultImg.begin<Vec3b>();
		MatIterator_<Vec3b>iteratorEnd =
			resultImg.end<Vec3b>();
		for (; iterator != iteratorEnd; iterator++)
		{
			(*iterator)[0] = LUT[((*iterator)[0])];
			(*iterator)[1] = LUT[((*iterator)[1])];
			(*iterator)[2] = LUT[((*iterator)[2])];
		}
	}
	return resultImg;
}
int main()
{
	Mat srcImg = imread("E:\\研究生资料\\老婆\\相册\\145kb.jpg");
	if (!srcImg.data)
		return -1;
	float kFractor1 = 0.3;
	float kFractor2 = 3.0;
	Mat result1 = gammaTransform(srcImg, kFractor1);
	Mat result2 = gammaTransform(srcImg, kFractor2);
	imshow("srcImg", srcImg);
	imshow("result1", result1);
	imshow("result2", result2);
	waitKey(0);
	return 0;
}
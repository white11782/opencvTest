#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat linearTransform(Mat srcImg, float a, int b)
{
	if (srcImg.empty())
	{
		cout << "No data!" << endl;
	}
	const int nRows = srcImg.rows;
	const int nCols = srcImg.cols;
	Mat resultImg =
		Mat::zeros(srcImg.size(), srcImg.type());
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			for (int c = 0; i < 3; i++)
			{
				resultImg.at<Vec3b>(i, j)[c] =
					saturate_cast<uchar>(a *
					(srcImg.at<Vec3b>(i, j)[c]) + b);
			}
		}
	}
	return resultImg;
}
int main()
{
	Mat srcImg = imread("E:\\研究生资料\\老婆\\相册\\145kb.jpg");
	if (!srcImg.data)
		return -1;
	float a = 1.2;
	int b = 10;
	Mat new_image = linearTransform(srcImg, a, b);
	imshow("srcImg", srcImg);
	imshow("new_image", new_image);
	waitKey(0);
	return 0;
}
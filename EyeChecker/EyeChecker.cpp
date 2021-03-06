// EyeChecker.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>

#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>
//using namespace Mat;
using namespace cv;
using namespace std;

const float param_13 = 1.0f / 3.0f;
const float param_16116 = 16.0f / 116.0f;
const float Xn = 0.950456f;
const float Yn = 1.0f;
const float Zn = 1.088754f;



void RGB2XYZ(float R, float G, float B, float *X, float *Y, float *Z)
{
	*X = 0.412453f * R + 0.357580f * G + 0.180423f * B;
	*Y = 0.212671f * R + 0.715160f * G + 0.072169f * B;
	*Z = 0.019334f * R + 0.119193f * G + 0.950227f * B;
}

void XYZ2Lab(float X, float Y, float Z, float *L, float *a, float *b)
{
	float fX, fY, fZ;

	X /= Xn;
	Y /= Yn;
	Z /= Zn;

	if (Y > 0.008856f)
		fY = pow(Y, param_13);
	else
		fY = 7.787f * Y + param_16116;

	*L = 116.0f * fY - 16.0f;
	*L = *L > 0.0f ? *L : 0.0f;

	if (X > 0.008856f)
		fX = pow(X, param_13);
	else
		fX = 7.787f * X + param_16116;

	if (Z > 0.008856)
		fZ = pow(Z, param_13);
	else
		fZ = 7.787f * Z + param_16116;

	*a = 500.0f * (fX - fY);
	*b = 200.0f * (fY - fZ);
}

void RGB2Lab(float R, float G, float B, float *L, float *a, float *b)
{
	float X = 0.0f, Y = 0.0f, Z = 0.0f;
	RGB2XYZ(R, G, B, &X, &Y, &Z);
	XYZ2Lab(X, Y, Z, L, a, b);
}

enum ConvolutionType {
	/* Return the full convolution, including border */
	CONVOLUTION_FULL,

	/* Return only the part that corresponds to the original image */
	CONVOLUTION_SAME,
	/* Return only the submatrix containing elements that were not influenced by the border */
	CONVOLUTION_VALID
};

Mat conv2(const Mat &img, const Mat& ikernel, ConvolutionType type)
{
	Mat dest;
	Mat kernel;
	flip(ikernel, kernel, -1);
	Mat source = img;
	if (CONVOLUTION_FULL == type)
	{
		source = Mat();
		const int additionalRows = kernel.rows - 1, additionalCols = kernel.cols - 1;
		copyMakeBorder(img, source, (additionalRows + 1) / 2, additionalRows / 2, (additionalCols + 1) / 2, additionalCols / 2, BORDER_CONSTANT, Scalar(0));
	}
	Point anchor(kernel.cols - kernel.cols / 2 - 1, kernel.rows - kernel.rows / 2 - 1);
	int borderMode = BORDER_CONSTANT;
	filter2D(source, dest, img.depth(), kernel, anchor, 0, borderMode);

	if (CONVOLUTION_VALID == type)
	{
		dest = dest.colRange((kernel.cols - 1) / 2, dest.cols - kernel.cols / 2).rowRange((kernel.rows - 1) / 2, dest.rows - kernel.rows / 2);
	}
	return dest;
}

int main()
{
	Mat srcImage;//原图像
	Mat logoImage;//标志图
	vector< Mat > channels;//定义通道
	Mat  imageBlueChanne;//以下分别为蓝绿红三个通道
	Mat  imageGreenChanne;
	Mat  imageRedChanne;

	Mat fitter = Mat::ones(5,5,CV_32F);
	fitter *= 0.04 ;
	Mat image;
	image = imread("D:\\code\\app\\EyeChecker\\EyeChecker\\1a.jpg");
	double fScale = 1;//缩放系数
	//卷积
	//计算目标图像的大小
	Size dsize = Size(image.cols*fScale, image.rows*fScale);
	
	Mat imagedst = Mat(dsize, CV_32S);
	resize(image, imagedst, dsize);

	split(imagedst, channels);
	
	Mat b_img = channels.at(0);
	Mat g_img = channels.at(1);
	Mat r_img = channels.at(2);
		
	Mat Image_2(dsize, CV_32FC3);
	image.convertTo(Image_2, CV_32FC3);

	{	//Mat r(imagedst.rows, imagedst.cols, CV_32FC1);
	//Mat g(imagedst.rows, imagedst.cols, CV_32FC1);
	//Mat b(imagedst.rows, imagedst.cols, CV_32FC1);
	}
	
	Mat R = conv2(r_img,fitter,CONVOLUTION_SAME);
	Mat G = conv2(g_img, fitter, CONVOLUTION_SAME);
	Mat B = conv2(b_img, fitter, CONVOLUTION_SAME);
	

	vector <Mat>merg_img(3);
	merg_img[0] = B;
	merg_img[1] = G;
	merg_img[2] = R;

	Mat imgRGB(imagedst.size(), imagedst.type());
	merge(merg_img,imgRGB);//将向量转换成矩阵imgRGB

	Mat imgLAB;
	cvtColor(imgRGB,imgLAB,CV_BGR2Lab);
	Mat RBG;
	{ 
		Mat samples(imgLAB.cols*imagedst.rows, 1, CV_32FC3);
		//标记矩阵，32位整形 
		Mat labels(imgLAB.cols*imagedst.rows, 1, CV_32SC1);
		uchar* p;
		int i, j, k = 0;
		for (i = 0; i < imgLAB.rows; i++)
		{
			p = imgLAB.ptr<uchar>(i);
			for (j = 0; j < imgLAB.cols; j++)
			{
				samples.at<Vec3f>(k, 0)[0] = float(p[j * 3]);
				samples.at<Vec3f>(k, 0)[1] = float(p[j * 3 + 1]);
				samples.at<Vec3f>(k, 0)[2] = float(p[j * 3 + 2]);
				k++;
			}
		}

		int clusterCount = 2;
		Mat centers(clusterCount, 1, samples.type());
		kmeans(samples, clusterCount, labels,
			TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0),
			2, KMEANS_PP_CENTERS, centers);

		Mat img1(imgLAB.rows, imgLAB.cols, CV_8UC1);

		float step = 255 / (clusterCount - 1);
		k = 0;
		for (i = 0; i < img1.rows; i++)
		{
			p = img1.ptr<uchar>(i);
			for (j = 0; j < img1.cols; j++)
			{
				int tt = labels.at<int>(k, 0);
				k++;
				p[j] = 255 - tt * step;
			}
		}

		//Mat pixel_labels = img1.reshape();

		double fScale = 1;//缩放系数
//卷积
//计算目标图像的大小
		Size dsize = Size(image.cols*fScale, image.rows*fScale);

		Mat imagedst = Mat(dsize, CV_32S);
		resize(image, imagedst, dsize);

		double fScale1 = 0.4;//缩放系数
//卷积
//计算目标图像的大小
		Size dsize1 = Size(img1.cols*fScale1, img1.rows*fScale1);

		Mat imagedst1 = Mat(dsize1, CV_32S);
		resize(img1, imagedst1, dsize1);

		namedWindow("K-Means分割效果", 1);
		imshow("K-Means分割效果", imagedst1);
		namedWindow("二维卷积效果", 2);
		imshow("二维卷积效果", imgLAB);
		waitKey();
		return 0;

	}


	

		return 0;
	//{
	//	Mat img = imread("D:\\code\\app\\EyeChecker\\EyeChecker\\1a.jpg");
	//	namedWindow("Source Image", 0);
	//	imshow("Source Image", img);
	//	//生成一维采样点,包括所有图像像素点,注意采样点格式为32bit浮点数。 
	//	Mat samples(img.cols*img.rows, 1, CV_32FC3);
	//	//标记矩阵，32位整形 
	//	Mat labels(img.cols*img.rows, 1, CV_32SC1);
	//	uchar* p;
	//	int i, j, k = 0;
	//	for (i = 0; i < img.rows; i++)
	//	{
	//		p = img.ptr<uchar>(i);
	//		for (j = 0; j < img.cols; j++)
	//		{
	//			samples.at<Vec3f>(k, 0)[0] = float(p[j * 3]);
	//			samples.at<Vec3f>(k, 0)[1] = float(p[j * 3 + 1]);
	//			samples.at<Vec3f>(k, 0)[2] = float(p[j * 3 + 2]);
	//			k++;
	//		}
	//	}

	//	int clusterCount = 4;
	//	Mat centers(clusterCount, 1, samples.type());
	//	kmeans(samples, clusterCount, labels,
	//		TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0),
	//		3, KMEANS_PP_CENTERS, centers);
	//	//我们已知有3个聚类，用不同的灰度层表示。 
	//	Mat img1(img.rows, img.cols, CV_8UC1);
	//	float step = 255 / (clusterCount - 1);
	//	k = 0;
	//	for (i = 0; i < img1.rows; i++)
	//	{
	//		p = img1.ptr<uchar>(i);
	//		for (j = 0; j < img1.cols; j++)
	//		{
	//			int tt = labels.at<int>(k, 0);
	//			k++;
	//			p[j] = 255 - tt * step;
	//		}
	//	}

	//	namedWindow("K-Means分割效果", 0);
	//	imshow("K-Means分割效果", img1);
	//	waitKey();
	//	return 0;
	//}


	waitKey();

}


//void Conv2D(int** filter, int** arr, int** res, int filterW, int filterH, int arrW, int arrH)
//{
//	int temp;
//
//	for (int i = 0; i < filterH + arrH - 1; i++)
//	{
//		for (int j = 0; j < filterW + arrW - 1; j++)
//		{
//			temp = 0;
//			for (int m = 0; m < filterH; m++)
//			{
//				for (int n = 0; n < filterW; n++)
//				{
//					if ((i - m) >= 0 && (i - m) < arrH && (j - n) >= 0 && (j - n) < arrW)
//					{
//						temp += filter[m][n] * arr[i - m][j - n];
//					}
//				}
//			}
//			res[i][j] = temp;
//		}
//	}
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件


#include<iostream>
#include<math.h>
#include "pch.h"

#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

//ȫ�ֱ���
Vec3b *g_ColorVectorSpace;                                 //��ɫ�ռ�����

//��������
void color_CNN(Mat srcImage, Mat &drawImage);              //������ɫ�ռ���������ģʽ���෨(Center Nearest Neighbor, CNN)
int Calculation_CNN(Vec3b src, Vec3b vectorSpace);         //������벢������С����Ŀռ���������
void InitColorVectorSpace();                               //��ʼ����ɫ�ռ�����

int main()
{
	Mat srcImage = imread("D:\\code\\app\\EyeChecker\\EyeChecker\\1a.jpgg");
	Mat drawImage(srcImage.size(), CV_8UC3, Scalar(255, 255, 255));

	color_CNN(srcImage, drawImage);

	imshow("ԭʼͼ", srcImage);
	imshow("Ч��ͼ", drawImage);

	waitKey(0);
	return 0;
}

void InitColorVectorSpace()
{
	g_ColorVectorSpace = new Vec3b[8];

	//BGRģ�ͣ�����RGB��
	g_ColorVectorSpace[0] = Vec3b(0, 0, 0);                //��ɫ
	g_ColorVectorSpace[1] = Vec3b(255, 0, 0);              //��ɫ
	g_ColorVectorSpace[2] = Vec3b(0, 255, 0);              //��ɫ
	g_ColorVectorSpace[3] = Vec3b(255, 255, 0);            //��ɫ
	g_ColorVectorSpace[4] = Vec3b(0, 0, 255);              //��ɫ
	g_ColorVectorSpace[5] = Vec3b(255, 0, 255);            //���ɫ
	g_ColorVectorSpace[6] = Vec3b(0, 255, 255);            //��ɫ
	g_ColorVectorSpace[7] = Vec3b(255, 255, 255);          //��ɫ
}

void color_CNN(Mat srcImage, Mat &drawImage)
{
	//��ʼ����ɫ�ռ�
	InitColorVectorSpace();

	//����ͼ������
	int nearestPosition = 0;
	for (int y = 0; y < srcImage.rows; y++)
	{
		for (int x = 0; x < srcImage.cols; x++)
		{
			nearestPosition = Calculation_CNN(srcImage.at<Vec3b>(y, x), g_ColorVectorSpace);
			drawImage.at<Vec3b>(y, x) = g_ColorVectorSpace[nearestPosition];
		}
	}
}

int Calculation_CNN(Vec3b src, Vec3b vectorSpace)
{
	return 0;
}

int Calculation_CNN(Vec3b src, Vec3b *vectorSpace)
{
	int nearestPosition = 0;
	double distance;
	distance = sqrt(pow(double(src[0] - vectorSpace[0][0]), 2) + pow(double(src[1] - vectorSpace[0][1]), 2) + pow(double(src[2] - vectorSpace[0][2]), 2));

	for (int i = 1; i < 8; i++)
	{
		if (distance > sqrt(pow(double(src[0] - vectorSpace[i][0]), 2) + pow(double(src[1] - vectorSpace[i][1]), 2) + pow(double(src[2] - vectorSpace[i][2]), 2)))
		{
			distance = sqrtl(pow(double(src[0] - vectorSpace[i][0]), 2) + pow(double(src[1] - vectorSpace[i][1]), 2) + pow(double(src[2] - vectorSpace[i][2]), 2));
			nearestPosition = i;
		}
	}
	return nearestPosition;
}
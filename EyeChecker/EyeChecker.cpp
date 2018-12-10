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

//Mat cornea(Mat &img, Mat &x, Mat &y) {
//	double max_x = 0;
//	double min_x = 0;
//	minMaxLoc(img, &min_x, &max_x);
//	double max_y ;
//	double min_y ;
//	minMaxLoc(img, &min_y, &max_y);
//
//	int x0 =(round)(max_x + min_x) / 2;
//	int y0 = (round)(max_y + min_y) / 2;
//	int b = (round)(max_y - min_y) / 2;
//	int a = (round)(max_x - min_x) / 2;
//
//	vector< Mat > channels1;
//	int L1 = img.rows;
//	int L2 = img.cols;
//	Mat result(L1,L2,CV_32F);
//	split(img, channels1);
//	/*Mat l1 = channels1.at(0);
//	Mat l2 = channels1.at(1);
//	Mat l3 = channels1.at(2);*/
//	for (int i = 0; i < L1; i++)
//	{
//		for (int j = 0; j < L2; j++)
//		{
//			if ((i - x0)*(i - x0) / (a*a) + (j - y0)*(j - y0) / (b*b) >= 1)
//			{
//				Vec3b pixel;
//				pixel[0] = 255;
//				pixel[1] = 255;
//				pixel[2] = 255;
//				result.at<Vec3b>(i, j) = pixel;
//			}
//		}
//	}
//	return result;
//}

Mat kouqu(Mat &mask, Mat & RGB) {
	//take the mask of the original image
	// 
	vector<Mat> channels;
	split(RGB, channels);
	Mat b = channels.at(0);
	Mat g = channels.at(1);
	Mat r = channels.at(2);
	for (int i = 0; i < RGB.rows; i++)
	{
		uchar* b1 = b.ptr<uchar>(i);
		uchar* g1 = g.ptr<uchar>(i);
		uchar* r1 = b.ptr<uchar>(i);
		uchar* m = mask.ptr<uchar>(i);

		for (int j = 0; j < RGB.cols; j += 1)
		{
			if (m[j] != 0) {
				b1[j] = 0;
				g1[j] = 0;
				r1[j] = 0;
			}
		}
	}
	vector <Mat>merg_img(3);
	merg_img[0] = b;
	merg_img[1] = g;
	merg_img[2] = r;

	Mat imgRGB(RGB.size(), RGB.type());
	merge(merg_img, imgRGB);//将向量转换成矩阵imgRGB
	return imgRGB;
}

//Mat fill_glitter(const Mat &I,const Mat &rgb) {
//	double channel1min = 110.000;
//	double channel1max = 255.000;
//	double channel2min = 120.000;
//	double channel2max = 255.000;
//	// define thresholds for channel 3 based on histogram settings
//	double channel3min = 190.000;
//	double channel3max = 255.000;
//	// create mask based on chosen histogram thresholds		
//	//vector<Mat> channels;
//	//split(rgb, channels);
//	//Mat b = channels.at(0);
//	//Mat g = channels.at(1);
//	//Mat r = channels.at(2);
//
//	vector<Mat> channels;
//	split(I, channels);
//	Mat b = channels.at(0);
//	Mat g = channels.at(1);
//	Mat r = channels.at(2);
//	int BW = 0;//bw 为BW=~BW;最后的值
//	for (int i = 0; i < b.rows; i++)
//	{
//		uchar* b1 = b.ptr<uchar>(i);
//		uchar* g1 = g.ptr<uchar>(i);
//		uchar* r1 = r.ptr<uchar>(i);
//		for (int j = 0; j < b.cols; j++)
//		{
//			if (b1[j] >= channel3min && b1[j] <= channel3max
//				&& g1[j] >= channel2min && g1[j] <= channel2max
//				&& r1[j] >= channel1min && r1[j] <= channel3max
//				) {
//				BW--;
//			}
//			else {
//				BW++;
//			}
//
//				}
//	}
//
//	for (int i = 0; i < 1000; i++)
//	{
//		vector<Mat> channels;
//		split(rgb, channels);
//		Mat b = channels.at(0);
//		Mat g = channels.at(1);
//		Mat r = channels.at(2);
//
//		for (int i = 0; i < BW; i++)
//		{
//
//
//
//		}
//	}
//		
//
//	}


Mat my_green(const Mat &I_gb1, const Mat &I_gb2) {
	Mat I1 = I_gb1;
	Mat I2 = I_gb2;
	vector< Mat > channels1;
	vector< Mat > channels2;
	split(I1, channels1);
	Mat b_img1 = channels1.at(0);
	Mat g_img1 = channels1.at(1);
	split(I2, channels2);
	Mat b_img2 = channels2.at(0);
	Mat g_img2 = channels2.at(1);
	int a = 200;
	int sum1 = 0;
	int sum2 = 0;

	for (int i = 0; i < b_img1.rows; i++)
	{
		uchar* b = b_img1.ptr<uchar>(i);
		uchar* g = g_img1.ptr<uchar>(i);
		for (int j = 0; j < b_img1.cols; j += 1)
		{
			if (g[j] > 200 && b[j] < 200)
				sum1++;
		}
		
	}
	//find function one channels
	for (int i = 0; i < b_img1.rows; i++)
	{
		uchar* b = b_img2.ptr<uchar>(i);
		uchar* g = g_img2.ptr<uchar>(i);
		for (int j = 0; j < b_img1.cols; j++)
		{
			if (g[j] > 200 && b[j] < 200)
				sum2++;
		}

	}
	
	return sum1 > sum2 ? I_gb1 : I_gb2;

}

Mat my_green1(const Mat &I_gb1, const Mat &I_gb2) {
	Mat I1 = I_gb1;
	Mat I2 = I_gb2;
	vector< Mat > channels1;
	vector< Mat > channels2;

	split(I1, channels1);
	Mat b_img1 = channels1.at(0);
	Mat g_img1 = channels1.at(1);
	split(I2, channels2);
	Mat b_img2 = channels2.at(0);
	Mat g_img2 = channels2.at(1);
	int a = 200;
	int N_G1 = 0;
	int N_B1 = 0;
	int N_G2 = 0;
	int N_B2 = 0;
	//find
	for (int i = 0; i < b_img1.rows; i++)
	{
		uchar* b = b_img1.ptr<uchar>(i);
		uchar* g = g_img1.ptr<uchar>(i);
		for (int j = 0; j < b_img1.cols; j += 1)
		{
			if (b[j] > 0)
				N_B1++;
			if (g[j] > 0)
				N_G1++;
		}

	}
	//find function one channels
	for (int i = 0; i < b_img1.rows; i++)
	{
		uchar* b = b_img2.ptr<uchar>(i);
		uchar* g = g_img2.ptr<uchar>(i);
		for (int j = 0; j < b_img1.cols; j++)
		{
			if (b[j] > 0)
				N_B2++;
			if (g[j] > 0)
				N_G2++;
		}

	}
	double G1_ave;
	double B1_ave;
	double G2_ave;
	double B2_ave;
	for (int i = 0; i < b_img1.rows; i++)
	{
		uchar* b = b_img1.ptr<uchar>(i);
		uchar* g = g_img1.ptr<uchar>(i);
		for (int j = 0; j < b_img1.cols; j++)
		{
			if (b[j] > 0)
				B1_ave = b[j] / N_B1;
			if (g[j] > 0)
				G1_ave = g[j] / N_G1;
		}

	}
	for (int i = 0; i < b_img1.rows; i++)
	{
		uchar* b = b_img2.ptr<uchar>(i);
		uchar* g = g_img2.ptr<uchar>(i);
		for (int j = 0; j < b_img1.cols; j++)
		{
			if (b[j] > 0)
				B2_ave = b[j] / N_B2;
			if (g[j] > 0)
				G2_ave = g[j] / N_G2;
		}
	}
	int num_G1_255=0;
	int num_G2_255=0;
	for (int i = 0; i < b_img1.rows; i++)
	{
		uchar* g1 = g_img1.ptr<uchar>(i);
		uchar* g2 = g_img2.ptr<uchar>(i);
		for (int j = 0; j < b_img1.cols; j++)
		{
			if (g1[j] == 255)
				num_G1_255++;
			if (g2[j] == 255)
				num_G2_255++;
		}
	}
	cout << num_G1_255 <<"   "<< num_G2_255 << endl;
	if (G1_ave >= G2_ave && num_G1_255 >= num_G2_255) {
		return  I_gb1;
	}
	else if (G1_ave >= G2_ave && G1_ave > B1_ave)
		return I_gb1;
	else return I_gb2;
	
}

Mat kmeans(const Mat& image) {
	vector< Mat > channels;//定义通道
	Mat fitter = Mat::ones(5, 5, CV_32F);
	fitter *= 0.04;
	double fScale = 0.9;//缩放系数
	//卷积
	//计算目标图像的大小
	Size dsize = Size(image.cols*fScale, image.rows*fScale);
	Mat imagedst = Mat(dsize, CV_32S);
	resize(image, imagedst, dsize);
	cout << image.rows << " " << image.cols << endl;
	split(imagedst, channels);
	Mat b_img = channels.at(0);
	Mat g_img = channels.at(1);
	Mat r_img = channels.at(2);

	Mat Image_2(dsize, CV_32FC3);
	image.convertTo(Image_2, CV_32FC3);

	Mat R = conv2(r_img, fitter, CONVOLUTION_SAME);
	Mat G = conv2(g_img, fitter, CONVOLUTION_SAME);
	Mat B = conv2(b_img, fitter, CONVOLUTION_SAME);


	vector <Mat>merg_img(3);
	merg_img[0] = B;
	merg_img[1] = G;
	merg_img[2] = R;

	Mat imgRGB(imagedst.size(), imagedst.type());
	merge(merg_img, imgRGB);//将向量转换成矩阵imgRGB

	Mat imgLAB;
	cvtColor(imgRGB, imgLAB, CV_BGR2Lab);
	Mat RBG;
	
		Mat samples(imgLAB.cols*imgLAB.rows, 1, CV_32FC3);
		//标记矩阵，32位整形 
		Mat labels(imgLAB.cols*imgLAB.rows, 1, CV_32SC1);
		uchar* p;
		uchar* q;
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


		k = 0;
		//		img1 = imagedst;
		cout << imagedst.rows << " " << imagedst.cols << endl;

		cout << labels.rows << " " << labels.cols << endl;
		Mat img1(imgLAB.rows, imgLAB.cols, CV_8UC1);
		Mat img2(imgLAB.rows, imgLAB.cols, CV_8UC1);
		imagedst.convertTo(img1, CV_8UC1);
		imagedst.convertTo(img2, CV_8UC1);

		float step = 255 / (clusterCount - 1);
		k = 0;
		for (i = 0; i < img1.rows; i++)
		{
			p = img1.ptr<uchar>(i);
			q = img2.ptr<uchar>(i);
			for (j = 0; j < 3 * img1.cols; j += 3)
			{
				int tt = labels.at<int>(k, 0);
				k++;
				if (tt == 0) {
					p[j] = 255;
					p[j + 1] = 255;
					p[j + 2] = 255;
				}
				else {
					q[j] = 255;
					q[j + 1] = 255;
					q[j + 2] = 255;
				}
			}
		}
		Mat result1 = my_green1(img1, img2);
		
		return img1;

}



int main()
{
	Mat srcImage;//原图像
	Mat logoImage;//标志图

	


	Mat image;
	image = imread("D://mal//GUI3.23//处理图片//1a.jpg");
	
	Mat result = kmeans(image);
	Mat result1 = kmeans(result);
		
		




		//Mat pixel_labels = img1.reshape();
		double fScale1 = 1;//缩放系数
		//卷积
		//计算目标图像的大小
		//Size dsize1 = Size(imgRGB.cols*fScale1, imgRGB.rows*fScale1);
		//Mat imagedst1 = Mat(dsize1, CV_8UC1);
		//resize(img1, imagedst1, dsize1);
		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
		compression_params.push_back(100);
		imwrite("D:\\1a1211.jpg",result1,compression_params);
		namedWindow("K-Means分割效果", 0);
		imshow("K-Means分割效果", result1);
		//namedWindow("二维卷积效果", 0);
		//imshow("二维卷积效果", img1);
		waitKey();
		return 0;
	

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

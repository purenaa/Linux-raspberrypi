#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max = 256)
{
	int histSize[] = { bins };
	float range[] = { 0, (float)range_max };
	int channels[] = { 0 };
	const float* ranges[] = { range };

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

/*
Mat make_palatte(int rows)
{
	Mat hsv(rows, 1, CV_8UC3);
	for(int i=0; i < rows; i++)
	{
		uchar hue = saturate_cast<uchar>((float)i / rows * 180);
		hsv.at<Vec3b>(i) = Vec3b(hue, 255, 255);
	}
	cvtColor(hsv, hsv, COLOR_HSV2BGR);
	return hsv;
}
*/

void draw_histo(Mat hist, Mat &hist_img, Size size = Size(256, 200))
{
	//Mat hsv_palatte = make_palatte(hist.rows);

	hist_img = Mat(size, CV_8UC3, Scalar(255, 255, 255));
	float bin = (float)hist_img.cols / hist.rows;
	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

	for(int i=0; i<hist.rows; i++)
	{
		float start_x = (i * bin);
		float end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at <float>(i));

		//Scalar color = hsv_palatte.at<Vec3b>(i);
		//if(pt2.y>0) rectangle(hist_img, pt1, pt2, color, -1);
		if(pt2.y>0) rectangle(hist_img, pt1, pt2, Scalar(0), -1);
	}
	flip(hist_img, hist_img, 0);
}

void create_hist(Mat img, Mat &hist, Mat &hist_img)
{
	int histsize = 256, range = 256;
	calc_Histo(img, hist, histsize, range);
	draw_histo(hist, hist_img);
}

int main()
{
	Mat image = imread("../image/lena.bmp", 0);
	CV_Assert(!image.empty());
	Mat hist, dst1, dst2, hist_img, hist_img1, hist_img2;
	create_hist(image, hist, hist_img);

	Mat accum_hist = Mat(hist.size(), hist.type(), Scalar(0));
	accum_hist.at<float>(0) = hist.at<float>(0);
	for(int i = 1; i < hist.rows; i++) {
		accum_hist.at<float>(i) = accum_hist.at<float>(i - 1) + hist.at<float>(i);
	}

	accum_hist /= sum(hist)[0];
	accum_hist *= 255;
	dst1 = Mat(image.size(), CV_8U);
	for(int i=0; i < image.rows; i++) {
		for(int j=0; j < image.cols; j++) {
			int idx = image.at<uchar>(i, j);
			dst1.at<uchar>(i, j) = (uchar)accum_hist.at<float>(idx);
		}
	}

	equalizeHist(image, dst2);
	create_hist(dst1, hist, hist_img1);
	create_hist(dst2, hist, hist_img2);

	imshow("image", image),			imshow("img_hist", hist_img);
	imshow("dst1-User", dst1),		imshow("User_hist", hist_img1);
	imshow("dst2-OpenCV", dst2),	imshow("OpenCV_hist", hist_img2);
	waitKey();
	return 0;
}

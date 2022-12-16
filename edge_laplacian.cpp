#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("../image/lena.bmp", 0);
	CV_Assert(image.data);

	short data1[] = {		// 4방향 라플라시안 마스크
		0, 1, 0,			// 원소들
		1, -4, 1,
		0, 1, 0
	};
	short data2[] = {		// 8방향 라플라시안 마스크
		-1, -1, -1,			// 원소들
		-1, 8, -1,
		-1, -1, -1
	};

	Mat dst1, dst2, dst3;
	Mat mask4(3, 3, CV_16S, data1);		// short형 행렬 선언(행렬 선언 -음수값 때문에)
	Mat mask8(3, 3, CV_16S, data2);		

	filter2D(image, dst1, CV_16S, mask4);		// cv::filter2D() 통한 라플라시안 수행
	filter2D(image, dst2, CV_16S, mask8);
	Laplacian(image, dst3, CV_16S, 1);			// OpenCV 라플라시안 수행 함수

	/* 음수값 정리를 위해 절댓값 및 uchar 변환 한 번에 수행*/
	convertScaleAbs(dst1, dst1);				// 절댓값 및 uchar형 반환
	convertScaleAbs(dst2, dst2);
	convertScaleAbs(dst3, dst3);

	imshow("image", image), 			imshow("filter2D_4방향", dst1);
	imshow("filter2D_8방향", dst2),		imshow("Laplacian_OpenCV", dst3);
	waitKey();
	return 0;
}

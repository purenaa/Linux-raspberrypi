#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat m1(3, 5, CV_8UC1);				// 8bit unsigned Char형 채널이 1개 행렬 선언
	Mat m2(m1.size(), CV_32FC1);		// 32bit float형 채널이 1개 행렬 선언

	for(int i=0, k=0; i < m1.rows; i++)
	{
		uchar * ptr_m1 = m1.ptr(i);			// m1 행렬의 i행 첫 주소 반환
		float * ptr_m2 = m2.ptr<float>(i);
		for(int j=0; j < m1.cols; j++)
		{
			ptr_m1[j] = j;
			*(ptr_m2 + j) = (float)j;		// 포인터 접근 방식
		}
	}
	cout << "m1 = " << endl << m1 << endl << endl;
	cout << "m2 = " << endl << m2 << endl;
	return 0;
}

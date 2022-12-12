#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat m1(4, 3, CV_32FC3);
	cout << "Dimension number = " << m1.dims << endl;
	cout << "Number of rows = " << m1.rows << endl;
	cout << "Number of columns = " << m1. cols << endl;
	cout << "Matrix Size = " << m1.size() << endl << endl;

	cout << "Total number of elements = " << m1.total() << endl;
	cout << "The size of an element = " << m1.elemSize() << endl;
	cout << "Size of one element per channel = " << m1.elemSize() << endl << endl;

	cout << " Type = " << m1.type() << endl;
	cout << "Type (number of channels | depth) = " << ((m1.channels()-1) << 3) + m1.depth() << endl;
	cout << "Depth = " << m1.depth() << endl;
	cout << "Channel = " << m1.channels() << endl << endl;

	cout << "step = " << m1.step << endl;
	cout << "step1() = " << m1.step1() << endl;

	return 0;
}

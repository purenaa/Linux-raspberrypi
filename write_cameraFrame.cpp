#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void put_string(Mat &frame, string text, Point pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_SIMPLEX;
	putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);
	putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);
}

int main()
{
	VideoCapture capture(0);
	CV_Assert(capture.isOpened());

	double fps = 29.97;
	int delay = cvRound(1000.0 / fps);
	Size size(640, 360);
	int fourcc = VideoWriter::fourcc('D', 'X', '5', '0');

	//capture.set(CAP_PROP_FRAME_WIDTH, size.width);
	//capture.set(CAP_PROP_FRAME_HEIGHT, size.height);

	cout << "width x height : " << size << endl;
	cout << "VideoWirter::fourcc : " << fourcc << endl;
	cout << "delay : " << delay << endl;
	cout << "fps : " << fps << endl;
	
	VideoWriter writer;
	CV_Assert(writer.isOpened());

	for(;;) {
		Mat frame;
		capture >> frame;
		writer.open("../image/video_file.avi", fourcc, fps, size);
		writer << frame;

		imshow("카메라 영상보기", frame);
		if(waitKey(delay) >= 0)
			break;
	}
	return 0;
}

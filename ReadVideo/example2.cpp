#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/cvstd.hpp"
#include <opencv2/videoio/videoio_c.h>
#include <cctype>
using namespace cv;
bool isNumber(const char * str);
int main(int argc, char const *argv[])
{
	namedWindow("Example2", WINDOW_AUTOSIZE);
	namedWindow("Logpolar", WINDOW_AUTOSIZE);
	VideoCapture cap;
	if(!isNumber( argv[1]) )
		cap.open( String( argv[1] ) );
	else
		cap.open( atoi(argv[1]) );
	Mat frame, logpolar_frame;
	VideoWriter writer;
	double fps = cap.get( cv::CAP_PROP_FPS );
	Size size(
		(int)cap.get(CAP_PROP_FRAME_WIDTH)
		 ,(int)cap.get(CAP_PROP_FRAME_HEIGHT)
	);

	writer.open( argv[2], CV_FOURCC('M','J','P','G'), fps, size );
	while(true){
		cap >> frame;
		if( frame.empty() )
			break;
		cv::imshow("Example2", frame);
		logPolar(
			frame,
			logpolar_frame,
			Point2f(
				frame.cols/2,
				frame.rows/2
			),
			40,
			WARP_FILL_OUTLIERS
			);
		imshow("Logpolar",logpolar_frame);
		writer << logpolar_frame;

		if(cv::waitKey(1) >= 0 )
			break;
	}	
	destroyWindow("Example2");
	destroyWindow("Logpolar");

	return 0;
}

bool isNumber(const char * str){
	int i =0;
	while(*str != 0 ){
		if( !isdigit(str[i]) )
			return false;
		i++;
		str++;
	}
	return true;
}
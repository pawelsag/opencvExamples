#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main(int argc, char const *argv[])
{
	Mat img = imread(argv[1], -1);
	if(  img.empty() ) return -1;
	auto & data = img.data;
	
	for (uint i =0; i < img.cols * img.rows*3 ; i++)
	{
		std::cout << (int)(*(data + i)) << " ";
	}

	namedWindow("Example1", WINDOW_AUTOSIZE );
	imshow("Example1", img);
	waitKey( 0 );
	destroyWindow( "Example1" );
	
	return 0;
}
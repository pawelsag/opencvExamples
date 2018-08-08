#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include "blur.cpp"

using namespace cv;

void BlurTheImage(Mat image);
void DownSapleImage(Mat image);
void CannyDetector(Mat image);
int main(int argc, char const *argv[])
{
	Mat img = imread(argv[1], -1);
	if(  img.empty() ) return -1;
	
	BlurTheImage(img);
	// CannyDetector(img);
	
	return 0;
}

void BlurTheImage(Mat image){
	namedWindow("Example3", WINDOW_AUTOSIZE );
	namedWindow("Example3_1", WINDOW_AUTOSIZE );
	// namedWindow("Example3_2", WINDOW_AUTOSIZE );
	imshow("Example3", image);

	Mat out; 
	// GaussianBlur( image, out, Size(11,11) ,2,2); 
	// blur_std::BoxBlur(image, out, 11 ,11);
	blur_std::BoxBlurBetter(image, out, 11 ,11);
	// blur_std::MedianBlur(image, out, 5 );

	imshow("Example3_1", out);
	// imshow("Example3_2", out2);
	waitKey( 0 );
	destroyWindow("Example3");
	destroyWindow("Example3_1");

}
void DownSapleImage(Mat image){
	namedWindow("Example3", WINDOW_AUTOSIZE );
	namedWindow("Example3_1", WINDOW_AUTOSIZE );
	imshow("Example3", image);

	Mat out; 
	pyrDown(image, out);
	imshow("Example3_1", out);

	waitKey( 0 );
	destroyWindow("Example3");
	destroyWindow("Example3_1");

}

void CannyDetector(Mat image){
	namedWindow("Example3", WINDOW_AUTOSIZE );
	namedWindow("Example3_1", WINDOW_AUTOSIZE );
	imshow("Example3", image);

	Mat gray_img,out; 
	// gausian blur will remove the noises, but will destroy edges as well
	// GaussianBlur( image, gray_img, Size(1,1) ,3,3); 
	// GaussianBlur( gray_img, gray_img, Size(1,1), 3,3);
	cvtColor(image, gray_img, COLOR_BGR2GRAY);
	Canny(gray_img, out, 10,100,3,true);

	imshow("Example3_1", out);

	waitKey( 0 );
	destroyWindow("Example3");
	destroyWindow("Example3_1");

}
// This file contains my own implementation of some blure algorithms
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <algorithm>

namespace blur_types{
	struct RGB{
		uint16_t R,G,B;
	};
}

namespace blur_std
{

	template<typename T>
	decltype(auto) BoxBlur( T& src, T& dst, int xRange, int yRange ){
		// to take good average of each pixel i need to calculate
		// central part of each kernel
		// so my algorithms should be odd
		if(xRange % 2 == 0 || yRange % 2 == 0){
			printf("Range values have to be odd\n");
			exit(1);
		}
		// declare all necessary variables, to avoid calculations
		int x_offset= -xRange/2 , y_offset = -yRange/2;
		int delimiter_x = -x_offset ,delimiter_y = -y_offset;
		int width = src.cols, height =  src.rows;
		int count{0}, idx{0}; 

		blur_types::RGB averageColor;
		// create new Mat object to hold calculated values
		cv::Mat temp_dst = cv::Mat(src.rows , src.cols, src.type() );;
		
		
		// set pointer to data the algorithm operates on.
		auto & data_src = src.data;
		auto & data_dst = temp_dst.data;
		auto & temp_dst_copy = temp_dst.data;
		
		// pixel_i idicates active pixel
		// we have 3 colors for each pixel so we should service it appropriatly
		for(int row =0 ; row < height; row++ )
			for( int col =0 ; col < width*3; col += 3 ){
				
				// calculate index for current pixel;
				idx = (row * width * 3) + col;
				
				// calculate submatrix for each RGB 
				for(int y = y_offset; y <= delimiter_y ; y++ ){
					for(int x = x_offset; x <= delimiter_x; x++){
						if( col + x >= 0 &&  col + x < width*3 && row + y >=0 && row + y < height ){
							averageColor.B += data_src[ idx + x*3 + y*(width*3)     ];  
							averageColor.G += data_src[ idx + x*3 + y*(width*3) + 1 ];  
							averageColor.R += data_src[ idx + x*3 + y*(width*3) + 2 ];  
							count++;
						}	
									
				}
		 	}
			data_dst[idx    ] = uint8_t(averageColor.B / count);
			data_dst[idx + 1] = uint8_t(averageColor.G / count);
			data_dst[idx + 2] = uint8_t(averageColor.R / count);
			averageColor = {0};
			count = 0;
		}
		printf("%i %i, %i %i \n",data_dst[0],data_dst[1],temp_dst_copy[0],temp_dst_copy[1] );
		dst = temp_dst;
		return dst;
	}

	template<typename T>
	decltype(auto) MedianBlur( T& src, T& dst, int SquareRange){
		// to take good average of each pixel i need to calculate
		// central part of each kernel
		// so my algorithms should be odd
		if(SquareRange % 2 == 0 ){
			printf("Range values have to be odd\n");
			exit(1);
		}

		// declare all necessary variables, to avoid calculations
		int x_offset = -SquareRange/2;
		int y_offset = x_offset;
		int delimiter_x = -x_offset;
		int delimiter_y = delimiter_x;
		int width = src.cols, height =  src.rows;
		int idx{0}; 
		
		blur_types::RGB medianColor{0};
		// create new Mat object to hold calculated values
		cv::Mat temp_dst = cv::Mat(src.rows , src.cols, src.type() );;
		
		
		// set pointer to data the algorithm operates on.
		auto & data_src = src.data;
		auto & data_dst = temp_dst.data;
		
		// pixel_i idicates active pixel
		// we have 3 colors for each pixel so we should service it appropriatly
		for(int row =0 ; row < height; row++ )
			for( int col =0 ; col < width*3; col += 3 ){
				
				// calculate index for current pixel;
				idx = (row * width * 3) + col;
				
				// calculate submatrix for each RGB 
				for(int y = y_offset; y <= delimiter_y ; y++ ){
					for(int x = x_offset; x <= delimiter_x; x++){
						if( col + x*3 >= 0 &&  col + x*3 < width*3 && row + y >=0 && row + y < height ){
							medianColor.B = std::max( data_src[ idx + x*3 + y*(width*3)     ], (uint8_t)medianColor.B);  
							medianColor.G = std::max( data_src[ idx + x*3 + y*(width*3) + 1 ], (uint8_t)medianColor.G); 
							medianColor.R = std::max( data_src[ idx + x*3 + y*(width*3) + 2 ], (uint8_t)medianColor.R);   
						}	
									
				}
			}

			data_dst[idx    ] = uint8_t(medianColor.B);
			data_dst[idx + 2] = uint8_t(medianColor.R);
			data_dst[idx + 1] = uint8_t(medianColor.G);
			medianColor = {0};
		}
	
		dst = temp_dst;
		return dst;
	}

	template<typename T>
	decltype(auto) BoxBlurBetter( T& src, T& dst, int xRange, int yRange ){
		// to take good average of each pixel i need to calculate
		// central part of each kernel
		// so my algorithms should be odd
		if(xRange % 2 == 0 || yRange % 2 == 0){
			printf("Range values have to be odd\n");
			exit(1);
		}
		// declare all necessary variables, to avoid calculations
		int x_offset= -xRange/2 , y_offset = -yRange/2;
		int delimiter_x = -x_offset ,delimiter_y = -y_offset;
		int width = src.cols, height =  src.rows;
		int count{0}, idx{0}; 

		blur_types::RGB averageColor;
		// create new Mat object to hold calculated values
		cv::Mat temp_dst_x = cv::Mat(src.rows , src.cols, src.type() );;
		cv::Mat temp_dst_y = cv::Mat(src.rows , src.cols, src.type() );;
		
		
		// set pointer to data the algorithm operates on.
		auto & data_src = src.data;
		auto & data_dst = temp_dst_x.data;
		auto & final_dst = temp_dst_y.data;
		
		// pixel_i idicates active pixel
		// we have 3 colors for each pixel so we should service it appropriatly
		// calculate the color 
		for(int row =0 ; row < height; row++ )
			for( int col =0 ; col < width*3; col += 3 ){
				// calculate index for current pixel;
				idx = (row * width * 3) + col;
				// calculate submatrix for each RGB 
					for(int x = x_offset; x <= delimiter_x; x++){
						if( col + x*3 >= 0 &&  col + x*3 < width*3){
							averageColor.B += data_src[ idx + x*3     ];  
							averageColor.G += data_src[ idx + x*3 + 1 ];  
							averageColor.R += data_src[ idx + x*3 + 2 ];  
							count++;  
						}	
									
				}
		 	
			data_dst[idx    ] = uint8_t(averageColor.B / count);
			data_dst[idx + 1] = uint8_t(averageColor.G / count);
			data_dst[idx + 2] = uint8_t(averageColor.R / count);
			averageColor = {0};
			count = 0;
		}

		// calculate same for y
		// pixel_i idicates active pixel
		for( int col =0 ; col < width*3; col += 3 )
			for(int row =0 ; row < height; row++ ){
				// calculate index for current pixel;
				idx = (row * width * 3) + col;
				// calculate submatrix for each RGB 
					for(int y = y_offset; y <= delimiter_y ; y++ ){
						if( row + y >=0 && row + y < height ){
							averageColor.B += data_dst[ idx + y*(width*3)     ];  
							averageColor.G += data_dst[ idx + y*(width*3) + 1 ];  
							averageColor.R += data_dst[ idx + y*(width*3) + 2 ]; 
							count++; 
						}
					}
			final_dst[idx    ] = uint8_t(averageColor.B / count);
			final_dst[idx + 1] = uint8_t(averageColor.G / count);
			final_dst[idx + 2] = uint8_t(averageColor.R / count);
			averageColor = {0};
			count = 0;
		}
	
		dst = temp_dst_y;
		return dst;
	}

	
	
}

#include <stdio.h>
#include "ipp.h"
#include <opencv.hpp>

int ipp_rgb2gray(const Ipp8u * src, const int & src_step, Ipp8u * dst, const int & dst_step, const IppiSize & roiSize) {
	Ipp64u start, end;
	start = ippGetCpuClocks();
	ippiRGBToGray_8u_C3C1R(src, src_step, dst, dst_step, roiSize);
	end = ippGetCpuClocks();
	return (int)(end - start);
}

int opencv_rgb2gray(const cv::Mat & src, cv::Mat & dst) {
	Ipp64u start, end;
	start = ippGetCpuClocks();
	cv::cvtColor(src, dst, cv::COLOR_RGB2GRAY);
	end = ippGetCpuClocks();
	return (int)(end - start);	
}

int main() {
	cv::Mat src = cv::imread("meter.jpg");
	cv::Mat ipp_dst = cv::Mat(src.rows, src.cols, CV_8UC1);
	cv::Mat opencv_dst = cv::Mat(src.rows, src.cols, CV_8UC1);
	int src_step = src.cols * 3;
	int dst_step = src.cols;
	IppiSize roiSize = { src.cols, src.rows };

	int ipp_time = ipp_rgb2gray((const Ipp8u *)src.data, src_step, (Ipp8u *)ipp_dst.data, dst_step, roiSize);
	int opencv_time = opencv_rgb2gray(src, opencv_dst);

	cv::imshow("ipp_gray", ipp_dst);
	cv::imshow("opencv_gray", opencv_dst);
	
	printf("Clocks to cvtColor (ipp): %d \n", ipp_time);
	printf("Clocks to cvtColor (opencv): %d \n", opencv_time);
	printf("opencv / ipp = %f", 1.0 * opencv_time / ipp_time);

	cv::waitKey(0);

	return 0;
}

/*
 * FeatureExtractor.h
 *
 *  Created on: 04/dic/2012
 *      Author: francesco
 */

#ifndef FEATUREEXTRACTOR_H_
#define FEATUREEXTRACTOR_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>



class FeatureExtractor {
public:
	FeatureExtractor(cv::Mat img);
	virtual ~FeatureExtractor();
private:
	cv::Mat image;
};

#endif /* FEATUREEXTRACTOR_H_ */

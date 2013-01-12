#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "extractorUtilsTest.h"

void debugging() {
	/*

	cv::vector <cv::vector<cv::Point> > prova;
	cv::vector<cv::Point> p1;
	p1.push_back(cv::Point(181,45));
	p1.push_back(cv::Point(180,131));
	p1.push_back(cv::Point(267,132));
	p1.push_back(cv::Point(267,46));
	prova.push_back(p1);

	cv::vector<cv::Point> p2;
	p2.push_back(cv::Point(186,46));
	p2.push_back(cv::Point(182,128));
	p2.push_back(cv::Point(263,131));
	p2.push_back(cv::Point(266,50));

	prova.push_back(p2);

	printf("PRIMA\nF %d: ",1);
	for (unsigned int i=0;i<prova.size();i++){
			for (unsigned int j=0;j<prova.at(i).size();j++){
				printf("(%d,%d)  ",prova.at(i).at(j).x,prova.at(i).at(j).y);
			}
			printf("\n\n");
	}

	//ordino in verso antiorario ogni quaterna di vettori
	for ( unsigned int i = 0; i< prova.size(); i++ ) {
		prova.at(i) = sort4PointsClockwise(prova.at(i));
	}

	prova = deleteOverlapped(prova);


	printf("DOPO\nF %d: ",1);
	for (unsigned int i=0;i<prova.size();i++){
			for (unsigned int j=0;j<prova.at(i).size();j++){
				printf("(%d,%d)  ",prova.at(i).at(j).x,prova.at(i).at(j).y);
			}
			printf("\n\n");
	}
	ASSERTM("start writing tests", true);
	*/
}

cute::suite make_suite_extractorUtilsTest(){
	cute::suite s;
	s.push_back(CUTE(debugging));
	return s;
}




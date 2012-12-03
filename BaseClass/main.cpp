#include "src/Launcher.h"

int main(){

	Button * b = new Button(10,2,20,20,"ciao");
		Circle * c = new Circle(8, 10, 15);
		Quadrilateral * q = new Quadrilateral(1,22,31,4,53,6,37,855);
		Triangle * t = new Triangle(0,1,22,3,43,51);

		std::cout << "Launcher\n";

		std::cout << b->getChunk();
		std::cout << c->getChunk();
		std::cout << q->getChunk();

		std::cout << t->getChunk();

		Object * o = c;

		std::cout << o->getChunk();

		FeatureGetter *ba = new FeatureGetter();



		imshow("finestra",ba->getImage("./lena.jpg"));
		cv::waitKey(0);

		cv::VideoCapture cap = ba->getStream();
		ba->showVideo(cap);


		return 0;

}

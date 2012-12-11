#ifndef BASE_CLASS_EXCEPTIONS_H_
#define BASE_CLASS_EXCEPTIONS_H_
// Exceptions
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;


class InputException : public runtime_error {
public:
	InputException(string mex):	runtime_error(mex){}
};



class VerticalLineException: public runtime_error {
public:
	VerticalLineException(): runtime_error("Vertical Stright Line Exception"){}
};


class ParallelLinesException: public runtime_error {
public:
	ParallelLinesException(): runtime_error("Parallel Lines Exception"){}
};


class CoincidentLinesException: public runtime_error {
public:
	CoincidentLinesException(): runtime_error("Coincident Lines Exception"){}
};


class NotOverlappedSegmentException: public runtime_error {
public:
	NotOverlappedSegmentException(): runtime_error("NotOverlappedSegmentException"){}
};

#endif /* BASE_CLASS_EXCEPTIONS_H_ */

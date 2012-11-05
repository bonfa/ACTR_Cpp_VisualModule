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

#endif /* BASE_CLASS_EXCEPTIONS_H_ */

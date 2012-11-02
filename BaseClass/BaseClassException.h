// Exceptions
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;





class DivideByZeroException : public runtime_error
{
 public:
     DivideByZeroException() : runtime_error( "attempted to divide by zero" ) {}
};

class InputException : public runtime_error {
public:
	InputException(string mex):	runtime_error(mex){}
};



class VerticalLineException: public runtime_error {
public:
	VerticalLineException(): runtime_error("Vertical Stright Line Exception"){}
};

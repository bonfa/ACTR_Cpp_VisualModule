// Exceptions
#include <iostream>
#include <exception>

using namespace std;


class InputException: public exception
{
  virtual const char* what() const throw()
  {
    return "Input Exception";
  }

  virtual const char* what(string mex) const throw()
    {
	  return (string("Input Exception - ") + mex).c_str();
    }

}inputException;



class VerticalLineException: public exception
{
  virtual const char* what() const throw()
  {
    return "Vertical Stright Line Exception";
  }

  virtual const char* what(string mex) const throw()
    {
	  return (string("Input Exception - ") + mex).c_str();
    }
}verticalLineException;


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
      return ("Input Exception - " + mex);
    }
}inputException;


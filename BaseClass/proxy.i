// File name: proxy.i
%module proxy

%{
#include "proxy.h"
%}

// List of all the methods of the class
%Proxy::demo();

%include "proxy.h"

// End of proxy.i
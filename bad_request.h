#ifndef BAD_REQUEST_H
#define BAD_REQUEST_H

#include "refrence.h"

class Bad_request : public exception
{
public:
	virtual const char* what() const throw()
	{return "Bad Request";};
};

#endif
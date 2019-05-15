#ifndef NOT_FOUND_H
#define NOT_FOUND_H

#include "refrence.h"

class Not_found : public exception
{
public:
	virtual const char* what() const throw()
	{return "Not Found";};
};

#endif
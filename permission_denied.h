#ifndef PERMISSION_DENIED_H
#define PERMISSION_DENIED_H

#include "refrence.h"

class Permission_denied : public exception
{
public:
		virtual const char* what() const throw()
		{return "Permission Denied"};
};

#endif
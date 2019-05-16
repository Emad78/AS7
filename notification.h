#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "refrence.h"
#include "bad_request.h"
#include "not_found.h"
#include "permission_denied.h"

class Notification
{
private:
	string content;
	bool is_read;
public:
	Notification(string _content);
	~Notification();
	
};

#endif
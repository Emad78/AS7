#include "notification.h"

Notification::Notification(string _content)
: content(_content)
{
	is_read = false;
}

void Notification::set_status()
{
	is_read = true;
}

bool Notification::get_status()
{
	return is_read;
}
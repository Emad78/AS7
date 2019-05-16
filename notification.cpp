#include "notification.h"

Notification::Notification(string _content)
: content(_content)
{
	is_read = false;
}
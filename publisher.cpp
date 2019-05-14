#include "publisher.h"

Publisher::publisher(Input input, int _id)
: Person(input, _id)
{
	is_publisher = true;
	followers.clear();
}
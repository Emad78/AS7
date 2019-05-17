#include "coment.h"

Comment::Comment()
{}
int Comment::reply(Input input)
{
	replies.push_back(input.info[CONTENT]);
	return person_id;
}

void Comment::_delete()
{
	is_visible = false;
}
#include "coment.h"

Comment::Comment(string _content, int _id, int _person_id)
: content(_content), id(_id), person_id(_person_id), is_visible(true)
{
	replies.clear();
}
int Comment::reply(Input input)
{
	replies.push_back(input.info[CONTENT]);
	return person_id;
}

void Comment::_delete()
{
	is_visible = false;
}

bool Comment::get_is_visible()
{
	return is_visible;
}

ostream& operator<<(ostream& out, Comment* comment)
{
	out<<comment->id<<". "<<comment->content<<endl;
	for(int i = 0; i < comment->replies.size(); i++)
		out<<comment->id<<"."<<i+1<<". "<<comment->replies[i]<<endl;
}
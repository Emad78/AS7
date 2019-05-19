#ifndef COMENT_H
#define COMENT_H

#include "refrence.h"
#include "bad_request.h"
#include "not_found.h"
#include "permission_denied.h"

class Comment
{
private:
	int id, person_id;
	string content;
	bool is_visible;
	vector<string> replies;
public:
	Comment(string _content, int _id, int _person_id);
	bool get_is_visible();
	int reply(Input input);
	void _delete();
	~Comment();
	friend ostream& operator<<(ostream& out, Comment* comment);
};

#endif
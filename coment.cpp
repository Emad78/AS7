#include "coment.h"

Coment::Coment()
{}
int Coment::reply(Input input)
{
	replies.push_back(input.info[CONTENT]);
	return person_id;
}
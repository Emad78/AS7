#ifndef COMENT_H
#define COMENT_H

class Coment
{
private:
	int id, person_id;
	string content;
	vector<string> replies;
public:
	Coment();
	~Coment();
};

#endif
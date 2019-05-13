#include "system.h"

System::System()
{
	system_money = 0;
	command = new Command();
	now_user = NULL;	
}

System::~System()
{
	for(int i = films.size() - 1; i >= 0; i--)
		delete films[i];
	for(int i = users.size() - 1; i >= 0; i--)
		delete users[i];
	delete command;
	delete now_user;
}

void System::run()
{
	string line;
	while(true)
	{
		try
		{
			getline(cin, line);
			input = command.get_input(line);
			process();

		}catch(exception& ex)
		{
			cout<<ex.what()<<endl;
		}
	}
}
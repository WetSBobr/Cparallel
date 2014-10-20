#include <iostream>
#include "stdlib.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include "request.h"
#include "answer.h"

using namespace std;

bool FileExists (string fname);


class Server 
{
	private:
	
	Request R_;
	string dir_;
	
	
	public:
	Server ();
	Server (string dir);
	friend istream& operator>>(istream &, Server &);
	friend ostream& operator<<(ostream &, Server &);
	
	
};

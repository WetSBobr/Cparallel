#include <iostream>
#include "stdlib.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <fstream>
#include <unistd.h>

using namespace std;


class Answer 
{
	private:
	int code_;
	int type_;
	string filename_;
	
	public:
	Answer ();
	Answer (int code, int type, string filename);
	friend ostream& operator<<(ostream &, Answer &);
};

#include "answer.h"

using namespace std;

Answer::Answer ():
	code_ (404),
	type_ (-1),
	filename_ ()
{}
Answer::Answer (int code, int type, string filename):
	code_ (code),
	type_ (type),
	filename_ (filename)
{}

ostream& operator<<(ostream & out, Answer & A)
{
	out << "HTTP/1.0 " << A.code_ <<" Document follows" << endl;
	
	long size = 0;
	if (A.code_ != 404)
	{
		FILE* file = fopen (A.filename_.c_str (), "rb");
		fseek(file,0, SEEK_END);
		size = ftell (file);	
	}
	out << "Content-lenght: " << size << endl;
	out <<  endl;
	if (A.type_ == 1 || A.type_ == 3)
	{
		system (string ("cat " + A.filename_).c_str ());
		cout << endl;
	}
	
	return out;
}

#include "server.h"

using namespace std;

bool FileExists (string fname)
{
	return std::ifstream(fname) != NULL;
}

Server::Server ():
	R_ (),
	dir_ ()
{}
Server::Server (string dir):
	R_(),
	dir_ (dir)
{}

istream& operator>>(istream &in , Server & S)
{
	in >> S.R_;
	return in;
}

ostream& operator<<(ostream &out , Server & S)
{
	string filename = S.dir_+S.R_.GetFileName ();
	
	if (S.R_.GetType () == -1 || ! FileExists (filename))
	{
		Answer A (404, -1, filename);
		out << A;

	}
	else 
	{
		Answer A (200, S.R_.GetType (), filename);
		out << A;
	}
	
	return out;
}

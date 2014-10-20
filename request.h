#include <iostream>
#include "stdlib.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <fstream>
#include <unistd.h>

using namespace std;


class Pair
{
	private:
	
	string key_;
	string value_;
	
	public:
	Pair ();
	Pair (string key, string value);
	friend class Request;
	friend ostream& operator<< (ostream &, Pair &);
};


class Request
{
	private:
	
	int type_;
	vector <Pair> Post_;
	vector <Pair> Get_;
	string file_;
	string error_;
	int content_lenght_;


	int GetTypeAndFile (string str);
	int GetType (string type);
	int GetPost (string s);
	
	
	public:
	
	Request ();
	Request (int type, vector <Pair> Post, vector <Pair> Get);
	friend istream& operator>>(istream &, Request &);
	friend ostream& operator<<(ostream &, Request &);
	
	int GetType ();
	string GetFileName ();
	
	
};

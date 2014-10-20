#include "request.h"


using namespace std;


Pair::Pair ():
	key_ (),
	value_ ()
{
}
	
Pair::Pair (string key, string value = ""):
	key_ (key),
	value_ (value)
{
}
ostream& operator<< (ostream &out, Pair &P)
{
	out << P.key_  << " = " << P.value_;
	return out;
}



int Request :: GetType () 
{
	return type_;
}
string Request :: GetFileName () 
{
	return file_;
}


Request :: Request ():
	type_ (-1),
	Post_ (),
	Get_ (),
	file_ (),
	error_ (),
	content_lenght_ (-1)
{}

Request :: Request (int type, vector <Pair> Post, vector <Pair> Get):
	type_ (type),
	Post_ (Post),
	Get_ (Get)
{}

int Request::GetTypeAndFile (string s)
{
	smatch m, kv;
	regex e ("^(get|post|head) ([\\w/]*/\\w+\\.{0,1}\\w*)(\\?{0,1})((\\w+={0,1}\\w*&)*(\\w+={0,1}\\w*)) http/1.0$", regex_constants::ECMAScript | regex_constants::icase);
	regex key_value_reg ("(\\w+)={0,1}(\\w*)&{0,1}");

	if (regex_search (s,m,e)) 
	{
		type_ = GetType (m[1]);
		file_ = m[2];
		if (m[3] != "?")
		{
			return 1;
		}
		string param = 	m[4].str ();
		while (regex_search (param, kv, key_value_reg))
		{
			Get_.push_back (Pair (kv[1].str (), kv[2].str ()));
			param = kv.suffix().str();
		}

	}
	else 
	{
		error_ = s;
		return 0;
	}
	return 1;
}
int Request::GetType (string type)
{
	transform(type.begin(), type.end(), type.begin(), ::tolower);
	if (type == "get")
		return 1;
	if (type == "head")
		return 2;
	if (type == "post")
		return 3;
	return 0;
}

int Request::GetPost (string s)
{
	smatch m, kv;
	
	regex post_reg ("^(\\w+={0,1}\\w*&)*(\\w+={0,1}\\w*)$");
	regex key_value_reg ("(\\w+)={0,1}(\\w*)&{0,1}");
	if (regex_search (s,m,post_reg)) 
	{
		string param = 	m[0].str ();
		while (regex_search (param, kv, key_value_reg))
		{
			Post_.push_back (Pair (kv[1].str (), kv[2].str ()));
			param = kv.suffix().str();
		}
	}
	
	
	return 1;
}

istream& operator>>(istream & in, Request & R)
{
	string str;
	smatch m;
	regex content_lenght_reg ("^content-lenght: (\\d+)");
	
	while (!in.eof ())
	{
		getline (in, str);
		//transform(str.begin(), str.end(), str.begin(), ::tolower);
		if (R.type_ == -1)
		{
			if (R.GetTypeAndFile (str) == 0)
			{
				return in;
			}
		}
		else if (regex_search(str, m, content_lenght_reg))
		{
			istringstream  (m[1]) >> R.content_lenght_  ;

		}
		else if (str == "")
		{
			if (R.content_lenght_ > 0)
			{
				getline (in, str);
				R.GetPost (str);
			}
			return in;
		}
	}
	return in;
}

ostream& operator<<(ostream & out, Request & R)
{
	out << "type = " << R.type_ << endl;
	
	cout << "Post params:" << endl;
	for (auto x:R.Post_)
	{
		out << x << endl;
	}
	cout << "Get params:" << endl;
	for (auto x:R.Get_)
	{
		out << x << endl;
	}
	
	
	return out;
}

#include <iostream>
#include "stdlib.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include "server.h"

using namespace std;

int main (int argc, char ** argv)
{
	
	string filename = "";
	int par=0;
	while( (par = getopt(argc, argv, "d:h")) != -1)
	{
		switch (par)
		{
			case 'h':
				cout << "Server" << endl;
				break;
			case 'd':
				filename = optarg;
				break;
		}
	}
	Server S (filename);
	cin >> S;
	cout << S;
	
	
	return 0;
}

//vulnerable002.cpp
#include <iostream>
#include <fstream>

using namespace std;

void do_something(ifstream& fin) {
	char buf[1024];
	fin >> buf;
}

int main(int argc, char **argv) {
	char dummy[1024];
	ifstream fin;
	cout << "Vulnerable002 starts...\n";
	
	if (argc>=2) fin.open(argv[1]);
	if(fin) do_something(fin);
	
	cout << "Vulnerable002 ends...\n";
}

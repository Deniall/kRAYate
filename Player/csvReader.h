#ifndef CSVREADER_H
#define CSVREADER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class CSVReader{
public:

	static vector<vector<double> > readLines(string file);

	static vector<vector<string> > readLinesString(string file);

	static vector<int> readString(string str);

};

#endif

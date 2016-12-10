#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "vector2D.h"

using namespace std;

class Script{
	public:

	string path;
	double x;
	double y;
	double px;
	double py;
	int sprite;

	Script(string g_path);
    Script();

    double getValue(string s);
    void setValue(string first, double offset, string second);
    double getVariable(string s);
    void setVariable(string s, double value);
    double getFunction(string s);
    bool isInteger(const std::string & s);
    void parse();
};

#endif

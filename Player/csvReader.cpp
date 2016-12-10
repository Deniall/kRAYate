#include "csvReader.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

vector<vector<double> > CSVReader::readLines(string file){
	ifstream inFile;
    inFile.open(file.c_str());
    string r = "";
    vector<string> f = vector<string>();

    while(!inFile.eof()){
            inFile >> r;
            f.push_back(r);
    }
    inFile.close();
    vector<vector<double> > vals = vector<vector<double> >();
    for(int i = 0;i < f.size()-1;i ++){
    	int found = f[i].find(",");
    	int prevFound = -1;
    	vals.push_back(vector<double>());
    	while(found != string::npos){
    		vals[i].push_back(strtod(f[i].substr(prevFound+1,found).c_str(), NULL));
    		prevFound = found;
    		found = f[i].find(",",prevFound+1);
    	}
    }
    return vals;

}

vector<vector<string> > CSVReader::readLinesString(string file){
	ifstream inFile;
    inFile.open(file.c_str());
    string r = "";
    vector<string> f = vector<string>();

    while(!inFile.eof()){
            inFile >> r;
            f.push_back(r);
    }
    inFile.close();
    vector<vector<string> > vals = vector<vector<string> >();
    for(int i = 0;i < f.size()-1;i ++){
    	int found = f[i].find(",");
    	int prevFound = -1;
    	vals.push_back(vector<string>());
    	while(found != string::npos){
    		vals[i].push_back(f[i].substr(prevFound+1,found-(prevFound+1)).c_str());
    		prevFound = found;
    		found = f[i].find(",",prevFound+1);
    	}
    }
    return vals;

}

vector<int> CSVReader::readString(string str){
    vector<int> vals = vector<int>();
    int found = str.find(",");
    int prevFound = -1;
    while(found != string::npos){
        vals.push_back(atoi(str.substr(prevFound+1,found-(prevFound+1)).c_str()));
        prevFound = found;
        found = str.find(",",prevFound+1);
    }
    return vals;
}

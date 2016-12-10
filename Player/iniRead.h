#ifndef INIREAD_H
#define INIREAD_H

/* INCLUDES */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class iniRead
{
    public:
    /** \brief This is the function for reading a single field from one section of an ini file.
     *
     *
     * @author Breogan Hackett
     *
     */
    static string getField(string path,string section,string name){

        // Open file at the specified path.

        ifstream inFile;//ifstream to be able to read from the file
        inFile.open(path.c_str());
        if(inFile.fail()){
            cout << "Unable to open " + path << endl;
            return "";//if file couldn't open return an empty string
        }
        string r;//string to hold the current line of text in the file
        //navigate through the file until the correct section is found
        while(!inFile.eof()){
            inFile >> r;
            if(r == "["+section+"]"){
                //navigate through the section until it ends or the correct field is found.
                while(!inFile.eof()){
                    inFile >> r;
                    if(r.find("[") == 0){
                        break;
                    }
                    if(name.size()+1 < r.size()){
                        if(r.find(name+"=")!=string::npos){
                            int e = r.find("=");//position of the equalss sign in the line
                            inFile.close();
                            return r.substr(e+1,string::npos);
                        }
                    }
                }
                break;
            }
        }
        inFile.close();
        //cout << "Unable to find " << name << " in " << section << endl;
        return "";//if the particular field isn't found return an empty string

    }
    protected:

    private:
};

#endif // INIREAD_H

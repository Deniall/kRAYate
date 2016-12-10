#include "script.h"

Script::Script(string g_path)
{
    path = g_path;
}
Script::Script(){
    path = "none";
}

double Script::getValue(string s)
{
    if(getVariable(s)!=-100)
    {
        return getVariable(s);
    } else {
        int sindex_startbracket = s.find("(");
        int sindex_endbracket = s.find(")");

        string func = s.substr(0, sindex_startbracket);
        //string param = s.substr(sindex_startbracket, sindex_endbracket);

        if(func == "distance")
        {
            return getFunction(func);
        }
    }
}

void Script::setValue(string s_first, double offset, string s_second)
{
    double first = getVariable(s_first);
    double second = 0;
    second = strtod(s_second.c_str(), NULL);
    //istringstream(s_second) >> second;
    if(offset==0)
    {
    setVariable(s_first, second);
    } else {
        setVariable(s_first, first += (second * offset));
    }
}

double Script::getVariable(string s)
{
    if(s == "position.x") { return x; }
    if(s == "position.y") { return y; }
    if(s == "player.x") { return px; }
    if(s == "player.y") { return py; }
    return -100;
}

void Script::setVariable(string s, double value)
{
    if(s == "position.x") { x = value; }
    if(s == "position.y") { y = value; }
}

double Script::getFunction(string s)
{
    if(s == "distance")
    {
        Vector2D pl(px,py);
        Vector2D p(x,y);
        return p.distance(pl);
    }
}

bool Script::isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

void Script::parse()
{
    /* LOGIC */
    // open script file
    ifstream scriptfile ("Data/Scripts/" + path);
    string line;
    if (scriptfile.is_open())
    {
        while(getline(scriptfile,line))
        {
            string word[10];
            int i = 0;
            stringstream ssin(line);
            while (ssin.good() && i < 10)
            {
                ssin >> word[i];
                ++i;
            }

            if(word[0]=="if")
            {
                // get the two values that are compared
                double firstvalue = getValue(word[1]);
                //int firstvalue = 1;
                double secondvalue = 0;
                if(isInteger(word[4]))
                {
                    secondvalue = strtod(word[4].c_str(),NULL);
                    //istringstream(word[4]) >> secondvalue;
                } else {
                    secondvalue = getValue(word[4]);
                }

                bool truth = false;

                // check if they compare
                if(word[3] == "equal")
                {
                    if(firstvalue == secondvalue)
                    {
                        truth = true;
                    }
                }
                else if(word[3] == "morethan")
                {
                    if(firstvalue > secondvalue)
                    {
                        truth = true;
                    }
                }
                else if(word[3] == "lessthan")
                {
                    if(firstvalue < secondvalue)
                    {
                        truth = true;
                        cout<<firstvalue<<endl;
                    }
                }

                // if they compare, carry out the else statement
                if(truth == true)
                {
                    // check what to do with the variables
                    if(word[7] == "equals")
                    {
                        setValue(word[6],0,word[8]);
                    }
                    else if(word[7] == "decrementby")
                    {
                        setValue(word[6],-1,word[8]);
                    }
                    else if(word[7] == "incrementby")
                    {
                        setValue(word[6],+1,word[8]);
                    }
                }
            } else {
                // not an if statement
            }
        }
        scriptfile.close();
    }
}

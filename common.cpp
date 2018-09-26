#include "define.h"
#include "common.h"

#include <sstream>
#include <iostream>

using namespace std;

string fstream2string(const ifstream &in)
{
    ostringstream tmp; 
    tmp << in.rdbuf(); 
    return tmp.str();
}

bool charIsBlank(const char c)
{
    return (c == ' ') || (c == '\t') || (c == '\r') || (c == '\n');
}

void error(std::string str)
{
    cout << "Error: " << str << endl;
    exit(-1);
}
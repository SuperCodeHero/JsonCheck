#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stack>

#include <Windows.h>

#include "define.h"
#include "common.h"

using namespace std;

typedef stack<char, list<char> > StatusStack;

int main()
{
    StatusStack stack;
    bool is_start = false;
    int status = NOT_START;
    string json = fstream2string(ifstream("json.json"));
    for(auto i = 0; i < json.size(); ++i)
    {
        char c = json[i];
        if(status != AFTER_QUOTATION && charIsBlank(c))
            continue;
            
        
        switch(c)
        {
        case LBRACE:
        {
            switch(status)
            {
            case NOT_START:
            {
                stack.push(c);
                status = AFTER_LBRACE;
                break;
            }
            }
            break;
        }
        }

        switch(status)
        {
        case NOT_START:
        {
            if(c != LBRACE)
                error("begin '{'");
            
            stack.push(c);
            status = AFTER_LBRACE;
            break;
        }
        case AFTER_LBRACE:
        {
            if(c != QUOTATION)
                error("after '{' not string");
            
            stack.push(c);
            status = AFTER_QUOTATION;
            break;
        }
        case AFTER_QUOTATION:
        {
            if(c == '\n')
                error("'\"' no match");

            switch(c)
            {
            case QUOTATION:
            {
                char sc = stack.top();
                if(sc != QUOTATION)
                    error("'\" no match 2'");
                stack.pop();

                status = AFTER_QUOTATION_MATCHED;
                break;
            }
            default: break;
            }

            break;
        }
        case AFTER_QUOTATION_MATCHED:
        {
            switch(c)
            {
            case COLON:
            {

                break;
            }
            }
            break;
        }
        }

    }

    return 0;
}
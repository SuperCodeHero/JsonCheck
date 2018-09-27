#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stack>

#include <Windows.h>

#include "define.h"
#include "common.h"

using namespace std;

typedef stack<int, list<int> > StatusStack;

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

        switch(status)
        {
        case NOT_START:
        {
            if(c != LBRACE)
                error("begin '{'");
            
            status = AFTER_LBRACE;
            stack.push(status);
            break;
        }
        case AFTER_LBRACE:
        {
            switch(c)
            {
            case QUOTATION:
            {
                status = AFTER_QUOTATION;
                stack.push(status);
                break;
            }
            case RBRACE:
            {
                int ss = stack.top();
                if(ss != AFTER_LBRACE)
                    error("'}' no match");
                
                stack.pop();
                status = AFTER_RBRACE;
                stack.push(status);
                break;
            }
            default: error(string("char '") + c + "'");

            }

        }
        case AFTER_QUOTATION:
        {
            if(c == '\n')
                error("'\"' no match");

            if(c != QUOTATION)
                break;

            int ss = stack.top();
            if(ss != AFTER_QUOTATION)
                error("'\" no match 2'");
            stack.pop();

            ss = stack.top();
            switch(ss)
            {
            case AFTER_LBRACE:
            {
                status = BEFORE_VALUE_COLON;
                stack.push(status);
                break;
            }
            case JSON_VALUE:
            {
                stack.pop();
                status = AFTER_JSON_VALUE;
                stack.push(status);
                break;
            }
            //TODO: 
            }
            break;
        }
        case BEFORE_VALUE_COLON:
        {
            stack.pop();
            switch(c)
            {
            case COLON:
            {
                status = JSON_VALUE;
                stack.push(status);
                break;
            }
            default:error(" after ':' no value");
            }
            break;
        }
        case JSON_VALUE:
        {
            switch(c)
            {
            case QUOTATION:
            {
                status = AFTER_QUOTATION;
                stack.push(status);
                break;
            }
            //TODO:
            }
            break;
        }
        case AFTER_JSON_VALUE:
        {
            stack.pop();

            int ss = stack.top();
            switch(c)
            {
            case COMMA:
            {   
                break;
            }
            case RBRACE:
            {
                if(ss != AFTER_LBRACE)
                    error(string("char '") + c + "'");
                
                stack.pop();
                status = AFTER_RBRACE;
                stack.push(status);
                break;
            }
            case RBRACKET:
            {
                if(ss != AFTER_LBRACKET)
                    error(string("char '") + c + "'");
                
                stack.pop();
                status = AFTER_RBRACKET;
                stack.push(status);
                break;
            }
            default: error(string("char '") + c + "'");

            }
            break;
        }
        case AFTER_RBRACE:
        {
            stack.pop();
            int ss = stack.top();
            switch(c)
            {
            case RBRACE:
            {
                if(ss != JSON_VALUE)
                    error(string("char '") + c + "'");
                stack.pop();
                status = AFTER_JSON_VALUE;
                stack.push(status);
                break;
            }

            }
        }

        }

    }

    return 0;
}
#ifndef __COMMON_H__
#define __COMMON_H__
#include <string>
#include <fstream>

std::string fstream2string(const std::ifstream &in);
bool charIsBlank(const char c);
void error(std::string str);

#endif
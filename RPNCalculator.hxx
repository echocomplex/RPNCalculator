#ifndef RPN_CALCULATOR_HXX
#define RPN_CALCULATOR_HXX


#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <map>


unsigned short priority (char oper);

int translateToRPN (std::vector<std::string>& queue, const std::string& exercise);

long long calculate (const std::vector<std::string>& queue);


#endif // RPN_CALCULATOR_HXX
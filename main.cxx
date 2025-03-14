#include <string>
#include <vector>
#include <iostream>
#include "RPNCalculator.hxx"


int main (void) {
    std::string q;
    std::getline(std::cin, q);
    
    std::vector<std::string> unit;

    if (translateToRPN(unit, q) == 0) {
        std::cout << q << " = " << calculate(unit) << std::endl;
    }

    return 0;
}
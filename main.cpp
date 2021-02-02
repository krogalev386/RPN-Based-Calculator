#include "math_object.h"
#include "rpn_calculator.h"
#include <iostream>
#include <stack>

int main(){
    RPN_calculator calculator;
    std::cout << calculator.calc("1 2 3 4 + 7 8 + 6 * 4 / 11 + - + -") << std::endl;
}
#include "math_object.h"
#include "rpn_calculator.h"
#include "reader.h"
#include "translator.h"
#include <iostream>
#include <stack>

int main(){
    reader rdr;
    RPN_calculator calculator;
    rdr.read("1 2 3 4 + 7 8 + 6 * 4 / 11 + - + -");
    calculator.load_input_queue(rdr.get_queue());
    std::cout << calculator.calc() << std::endl;
}
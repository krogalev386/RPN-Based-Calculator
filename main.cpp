#include "math_object.h"
#include "rpn_calculator.h"
#include "reader.h"
#include "translator.h"
#include <iostream>
#include <stack>

int main(){
    reader rdr;
    translator transl;
    RPN_calculator calculator;
    //rdr.read("1 2 3 4 + 7 8 + 6 * 4 / 11 + - + -");
    rdr.read("3 *  ( 10 - 3 / ( 5 - 8 ) ) * 9");
    //std::cout << "Check" << std::endl;
    transl.infix_to_rpn(rdr.get_queue());
    calculator.load_input_queue(transl.get_rpn_queue());
    //calculator.load_input_queue(rdr.get_queue());
    std::cout << calculator.calc() << std::endl;
}
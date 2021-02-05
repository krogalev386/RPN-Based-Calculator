#include "../include/math_object.h"
#include "../include/rpn_calculator.h"
#include "../include/reader.h"
#include "../include/translator.h"
#include <iostream>
#include <stack>
#include <regex>

int main(){
    reader rdr;
    translator transl;
    RPN_calculator calculator;
    std::string str;

    std::cin >> str;
    while (str!="q"){
        rdr.read(str);
        transl.infix_to_rpn(rdr.get_queue());
        calculator.load_input_queue(transl.get_rpn_queue());
        std::cout << calculator.calc() << std::endl;
        std::cin >> str;
    }
}
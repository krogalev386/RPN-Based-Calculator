#include "rpn_calculator.h"
#include "math_object.h"
#include <iostream>
#include <string>
#include <sstream>

std::unique_ptr<math_object> RPN_calculator::get_item_left(){
    std::unique_ptr<math_object> result = std::move(left_stack.top());
    left_stack.pop();
    return result;
}

std::unique_ptr<math_object> RPN_calculator::get_item_right(){
    std::unique_ptr<math_object> result = std::move(right_stack.top());
    right_stack.pop();
    return result;
}

void RPN_calculator::read(const std::string str){

    while(!right_stack.empty())
        right_stack.pop();

    std::stringstream ss(str);
    std::string tmp_str;
    std::stack<std::string> tmp_stack;

    while (ss >> tmp_str)
        tmp_stack.push(tmp_str);

    while (!tmp_stack.empty()){
        std::string tmp = tmp_stack.top();
        tmp_stack.pop();

        std::unique_ptr<math_object> object;

        if (tmp == "+"){
            object = std::make_unique<operation>(operation::plus);
        } else if (tmp == "-") {
            object = std::make_unique<operation>(operation::minus);
        } else if (tmp == "*") {
            object = std::make_unique<operation>(operation::prod);
        } else if (tmp == "/") {
            object = std::make_unique<operation>(operation::divis);
        } else {
            object = std::make_unique<number>(std::stod(tmp));
        }
        right_stack.push(std::move(object));
    }
};

double RPN_calculator::calc(const std::string str){

    read(str);

    std::unique_ptr<math_object> item;
    std::unique_ptr<math_object> first_op;
    std::unique_ptr<math_object> second_op;
    std::unique_ptr<math_object> res;

    while (right_stack.size() > 0){

        item  = get_item_right();

        if (dynamic_cast<number*>(item.get()))
            left_stack.push(std::move(item));

        else if (dynamic_cast<operation*>(item.get())){

            second_op = get_item_left();
            first_op = get_item_left();

            number* n1 = dynamic_cast<number*>(first_op.get());
            number* n2 = dynamic_cast<number*>(second_op.get());
            operation* op = dynamic_cast<operation*>(item.get());

            std::unique_ptr<number> s_res = std::make_unique<number>(op->apply_operation(*n1, *n2));
            left_stack.push(std::move(s_res));
        }
    }   

    res = get_item_left();
    double result = dynamic_cast<number*>(res.get())->getNumber();
    return result;
};
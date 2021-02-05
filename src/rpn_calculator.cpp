#include "../include/rpn_calculator.h"
#include "../include/math_object.h"
#include <iostream>
#include <string>
#include <sstream>

std::unique_ptr<math_object> RPN_calculator::get_stack_item(){
    std::unique_ptr<math_object> result = std::move(calc_stack.top());
    calc_stack.pop();
    return result;
}

std::unique_ptr<math_object> RPN_calculator::get_queue_item(){
    std::unique_ptr<math_object> result = std::move(input_queue.front());
    input_queue.pop();
    return result;
}

void RPN_calculator::load_input_queue(std::queue<std::unique_ptr<math_object>> input){
    input_queue = std::move(input);
};

double RPN_calculator::calc(){

    std::unique_ptr<math_object> item;
    std::unique_ptr<math_object> first_op;
    std::unique_ptr<math_object> second_op;
    std::unique_ptr<math_object> res;

    while (input_queue.size() > 0){

        item  = get_queue_item();

        if (dynamic_cast<number*>(item.get()))
            calc_stack.push(std::move(item));

        else if (dynamic_cast<operation*>(item.get())){

            second_op = get_stack_item();
            first_op = get_stack_item();

            number* n1 = dynamic_cast<number*>(first_op.get());
            number* n2 = dynamic_cast<number*>(second_op.get());
            operation* op = dynamic_cast<operation*>(item.get());

            std::unique_ptr<number> s_res = std::make_unique<number>(op->apply_operation(*n1, *n2));
            calc_stack.push(std::move(s_res));
        }
    }   

    res = get_stack_item();
    double result = dynamic_cast<number*>(res.get())->getNumber();
    return result;
};
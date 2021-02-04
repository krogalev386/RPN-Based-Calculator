#include "translator.h"
#include <iostream>

void translator::infix_to_rpn(std::queue<std::unique_ptr<math_object>> input_queue){
    
    infix_queue = std::move(input_queue);

    std::unique_ptr<math_object> object;

    while (!infix_queue.empty()){

        object = std::move(infix_queue.front());
        infix_queue.pop();


        if (dynamic_cast<number*>(object.get())){
            rpn_queue.push(std::move(object));
        }

        else if (dynamic_cast<operation*>(object.get())){

            operation* current_op = dynamic_cast<operation*>(object.get());
            operation* top_operation;

            if ((!operator_stack.empty()) && dynamic_cast<operation*>(operator_stack.top().get()))
                top_operation = dynamic_cast<operation*>(operator_stack.top().get());
                
            while ((!operator_stack.empty() && dynamic_cast<operation*>(operator_stack.top().get()))
              && ((top_operation->precedence > current_op->precedence) 
              || (top_operation->precedence == current_op->precedence))){

                rpn_queue.push(std::move(operator_stack.top()));
                operator_stack.pop();

                if ((!operator_stack.empty()) && dynamic_cast<operation*>(operator_stack.top().get()))                
                    top_operation = dynamic_cast<operation*>(operator_stack.top().get());
            }
            operator_stack.push(std::move(object));
        }

        else if (dynamic_cast<bracket*>(object.get())){

            bracket* br = dynamic_cast<bracket*>(object.get());
            if (br->p == bracket::open){
                operator_stack.push(std::move(object));
            } else {
                bracket* top_bracket;
                if ((!operator_stack.empty()) && (dynamic_cast<bracket*>(operator_stack.top().get())))
                    top_bracket = dynamic_cast<bracket*>(operator_stack.top().get());
                while ((!operator_stack.empty()) && (top_bracket->p != bracket::open)){
                    rpn_queue.push(std::move(operator_stack.top()));
                    operator_stack.pop();
                    if ((!operator_stack.empty()) && (dynamic_cast<bracket*>(operator_stack.top().get())))
                        top_bracket = dynamic_cast<bracket*>(operator_stack.top().get());
                }
                if ((!operator_stack.empty()) && (dynamic_cast<bracket*>(operator_stack.top().get()))){
                    br = dynamic_cast<bracket*>(operator_stack.top().get());
                    if (br->p == bracket::open)
                        operator_stack.pop();
                }
            }
        }
    }

    while(!operator_stack.empty()){
        rpn_queue.push(std::move(operator_stack.top()));
        operator_stack.pop();
    }
};

std::queue<std::unique_ptr<math_object>> translator::get_rpn_queue(){
    return std::move(rpn_queue);
};

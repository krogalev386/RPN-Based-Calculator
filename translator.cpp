#include "translator.h"

void translator::infix_to_rpn(std::queue<std::unique_ptr<math_object>>& input_queue){
    
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
            while ((dynamic_cast<operation*>(operator_stack.top().get()))
              && ((dynamic_cast<operation*>(operator_stack.top().get())->precedence > current_op->precedence) 
              || (dynamic_cast<operation*>(operator_stack.top().get())->precedence == current_op->precedence))){
                rpn_queue.push(std::move(operator_stack.top()));
                operator_stack.pop();
            }
            operator_stack.push(std::move(object));
        }
        else if (dynamic_cast<bracket*>(object.get())){
            bracket* br = dynamic_cast<bracket*>(object.get());
            if (br->p == bracket::Perpose::open){
                operator_stack.push(std::move(object));
            } else {
                while (dynamic_cast<bracket*>(object.get())->p != bracket::Perpose::open){
                    rpn_queue.push(std::move(operator_stack.top()));
                    operator_stack.pop();
                }
                if (dynamic_cast<bracket*>(operator_stack.top().get())->p == bracket::Perpose::open)
                    operator_stack.pop();
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

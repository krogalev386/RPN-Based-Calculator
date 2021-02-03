#include "reader.h"
#include <iostream>

void reader::read(const std::string str){
 
    while(!internal_queue.empty())
        internal_queue.pop();

    std::stringstream ss(str);
    std::string tmp;

    while (ss >> tmp){
        
        std::unique_ptr<math_object> object;

        if (tmp == "+"){
            object = std::make_unique<operation>(operation::plus);
        } else if (tmp == "-") {
            object = std::make_unique<operation>(operation::minus);
        } else if (tmp == "*") {
            object = std::make_unique<operation>(operation::prod);
        } else if (tmp == "/") {
            object = std::make_unique<operation>(operation::divis);
        } else if (tmp == "(") {
            object = std::make_unique<bracket>(bracket("("));
        } else if (tmp == ")") {
            object = std::make_unique<bracket>(bracket(")"));
        } else {
            object = std::make_unique<number>(std::stod(tmp));
        }
        internal_queue.push(std::move(object));
    }

};

std::queue<std::unique_ptr<math_object>> reader::get_queue(){
    return std::move(internal_queue);
}
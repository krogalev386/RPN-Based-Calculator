#include "reader.h"
#include <iostream>

void reader::read(const std::string str){
 
    std::regex regexp("(\\(-[0-9]+\\.?[0-9]*\\))|([0-9]+\\.?[0-9]*)|([\\+\\-\\*\\/]|[\\(\\)])");

    std::regex regneg("\\(\\-[0-9]+\\.?[0-9]*\\)");
    
    std::string outstr = "";

    // add spaces
    for (auto it = std::sregex_iterator(str.begin(), str.end(), regexp); 
         it != std::sregex_iterator(); it++) { 
        std::smatch match; 
        match = *it; 
        if (std::regex_search(match.str(0), regneg)){
            std::string tmp = match.str(0);
            tmp = tmp.substr(1, tmp.size()-2);
            outstr += tmp + std::string(" ");
        }
        else
            outstr += match.str(0) + std::string(" ");
    }  

    while(!internal_queue.empty())
        internal_queue.pop();

    std::stringstream ss(outstr);
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
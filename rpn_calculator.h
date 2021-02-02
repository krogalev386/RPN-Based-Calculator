#include <stack>
#include <string>
#include "math_object.h"
#include <memory>


class RPN_calculator {
    
    std::stack<std::unique_ptr<math_object>> left_stack;
    std::stack<std::unique_ptr<math_object>> right_stack;

    std::unique_ptr<math_object> get_item_right();
    std::unique_ptr<math_object> get_item_left();

public:

    void read(const std::string str);
    double calc(const std::string str);
};
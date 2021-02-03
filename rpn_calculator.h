#include <stack>
#include <string>
#include <queue>
#include "math_object.h"
#include <memory>


class RPN_calculator {
    
    std::stack<std::unique_ptr<math_object>> calc_stack;
    std::queue<std::unique_ptr<math_object>> input_queue;

    std::unique_ptr<math_object> get_queue_item();
    std::unique_ptr<math_object> get_stack_item();

public:

    void load_input_queue(std::queue<std::unique_ptr<math_object>> input);
    double calc();
};
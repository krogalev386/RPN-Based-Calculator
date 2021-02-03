#pragma once

#include <stack>
#include <queue>
#include "math_object.h"
#include <memory>

class translator {
    std::stack<std::unique_ptr<math_object>> operator_stack;
    std::queue<std::unique_ptr<math_object>> infix_queue;
    std::queue<std::unique_ptr<math_object>> rpn_queue;

public:
    translator(){};
    ~translator(){};

    void infix_to_rpn(std::queue<std::unique_ptr<math_object>>& input_queue);
    std::queue<std::unique_ptr<math_object>> get_rpn_queue();
};
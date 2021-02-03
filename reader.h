#pragma once

#include <memory>
#include <string>
#include <sstream>
#include <queue>
#include "math_object.h"

class reader {
    std::queue<std::unique_ptr<math_object>> internal_queue;

public:
    void read(const std::string str);
    std::queue<std::unique_ptr<math_object>> get_queue();
};
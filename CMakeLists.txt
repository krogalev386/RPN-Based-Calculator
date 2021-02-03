project(rpn_based_calculator)

set(SOURCE main.cpp)

set(LIB_CALC rpn_calculator.cpp)
set(LIB_READ reader.cpp)
set(LIB_TRANS translator.cpp)

set(HEADER rpn_calculator.h math_object.h reader.h translator.h)

add_library(rpn_calculator STATIC ${LIB_CALC})
add_library(reader STATIC ${LIB_READ})
add_library(translator STATIC ${LIB_TRANS})

add_executable(main.out ${SOURCE})
target_link_libraries(main.out rpn_calculator reader translator)

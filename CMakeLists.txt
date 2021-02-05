project(rpn_based_calculator)

set(SOURCE src/main.cpp src/rpn_calculator.cpp src/reader.cpp src/translator.cpp)

#set(LIB_CALC src/rpn_calculator.cpp)
#set(LIB_READ src/reader.cpp)
#set(LIB_TRANS src/translator.cpp)

set(HEADER include/rpn_calculator.h include/math_object.h include/reader.h include/translator.h)

#add_library(rpn_calculator STATIC ${LIB_CALC})
#add_library(reader STATIC ${LIB_READ})
#add_library(translator STATIC ${LIB_TRANS})

add_executable(src/main.out ${SOURCE})
#target_link_libraries(main.out rpn_calculator reader translator)

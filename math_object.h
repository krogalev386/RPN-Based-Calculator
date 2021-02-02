#pragma once
#include <string>

class math_object {
public:
    virtual void f(){};
    virtual ~math_object(){};
};

class number : public math_object {
    double num;

public:
    number() { num = 0; }
    number(double num) : num(num) {};
    number(const number & other) { num = other.num; }
    number(const number && other) { num = other.num; }
    ~number(){}

    double getNumber() const { return num; }
    void setNumber(const double & num) { this->num = num; }
    void operator=(const number & other) { num = other.num; }
};

class operation : public math_object {
public:
    enum Op {plus, minus, prod, divis} oper;
    operation(Op oper):oper(oper) {}

    virtual ~operation() {};

    number apply_operation(const number & n1, const number & n2){
        if (oper == plus) {
            return number(n1.getNumber() + n2.getNumber());
        } else if (oper == minus) {
            return number(n1.getNumber() - n2.getNumber());            
        } else if (oper == prod) {
            return number(n1.getNumber() * n2.getNumber());            
        } else if (oper == divis) {
            return number(n1.getNumber() / n2.getNumber());
        } 
        return number(0);    
    }
};


class bracket : public math_object {
    enum Perpose {close, open};
    Perpose p;
public:
    bracket(const std::string & str){
        if (str == ")") { p = close; }
        else if (str == "(") { p = open; }
    }
    virtual ~bracket() = 0;
};
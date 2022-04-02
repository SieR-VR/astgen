#include <iostream>

#include "core/parser.h"
#include "core/internal_functions.h"

class MyStruct : public GLSL::Variable
{
public:
    GLSL::Float fl;
    GLSL::Int in;
    GLSL::Vec2 vec;

    MyStruct()
        : Variable("MyStruct"),
          fl("fl", this), in("in", this), vec("vec", this)
    {
        GLSL::record(this->tree);
    }
};

int main(int argc, char *argv[])
{
    using namespace GLSL;
    Struct<MyStruct> mystruct;

    std::function<MyStruct(Int &, Float &)> to_parse = [](Int &a1, Float &a2)
    {
        MyStruct st;
        st.in = a1;
        st.fl = a2;
        st.vec = Vec2(a2, a2);
        
        return st;
    };
    auto some_function = Parse(to_parse, "some_function");

    std::cout << mystruct.declaration
              << mystruct.definition
              << std::endl
              << some_function.declaration
              << some_function.definition;
    return 0;
}
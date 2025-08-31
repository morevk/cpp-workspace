#include <iostream>
#include <string>
#include <format>

class StrToInt
{
    std::string str;
    
    public:
    StrToInt(const std::string tstr): str(tstr){}

    operator int()
    {
        std::cout << "called for = " << str << std::endl;
        return std::stoi(str);
    }
};

template <typename T>
T max(T x, T y)
{
    std::cout << std::format("x typeid {}, y typeid {}\n", typeid(x).name(), typeid(x).name());
    std::cout << std::format("x = {}, y = {}\n", x, y);
    return x > y ? x : y;
}

int test_template_argument_deduction_main() {
    
    int num = StrToInt("65");
    double dnum =  StrToInt("66");
    char cnum = StrToInt("67");
    
    std::cout << std::format("num = {}, dnum = {}, cnum = {}\n", num, dnum, cnum);
    
    // max(StrToInt("68") , 6.2); // error no matching call
    // max(static_cast<int>(StrToInt("68")), 6.2), // error no matching call
    
    max(static_cast<int>(StrToInt("68")), static_cast<int>(6.2));
    
    max(static_cast<double>(StrToInt("69")), 6.2);
    
    max<int>(StrToInt("70") , 6.2);
    
    max<double>(StrToInt("71") , 6.2);
    
    return 0;
}
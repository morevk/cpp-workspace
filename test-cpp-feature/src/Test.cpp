#include <iostream>
#include "Test.h"
namespace Vishal{
	Test::Test()
	{
		i = 10;
	}
	void Test::f1()
	{
		f2(i);
	}
	void Test::f2(int j)
	{
		i = j;
		std::cout << "void Test::f2(int j)" << std::endl;
	}
	// void Test::f2(const int j)
	// {
	// 	std::cout << "void Test::f2(const int j)" << std::endl;
	// }
	// void Test::f2(int &j)
	// {
	// 	std::cout << "void Test::f2(int &j)" << std::endl;
	// }
	// void Test::f2(const int &j)
	// {
	// 	std::cout << "void Test::f2(const int &j)" << std::endl;
	// }
    void Test::f2(int i) const
    {
		std::cout << "void Test::f2(int i) const" << std::endl;
    }
}

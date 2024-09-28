#if 1
#include <iostream>
#include <iomanip>

#include "Test.h"

int test_hello_main()
{
   //using namespace Vishal;
   using Vishal::Test;

   Test t;
   t.f1(); 

    std::cout << "Hello" << std::endl;

    return 0; 
}
#endif
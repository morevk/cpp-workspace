#include <iostream>

//Returns r-value
int Add(int x, int y) {
	return x + y;
}

//Return l-value
int& Transform(int &x) {
	x *= x;
	return x;
}

//Return l-value reference to static variable
int& Transform(int &&x) {
	x *= x;
	static int n = x;
	return n;
}

void Print(int &x) {
	std::cout << "Print(int&)" << std::endl; 
}
void Print(const int &x) {
	std::cout << "Print(const int&)" << std::endl;

}
void Print(int &&x) {
	std::cout << "Print(int &&)" << std::endl;
}
int getInt() {
    int i = 10;

    return i;
}
int* setInt() {
    static int i = 10;

    return &i;
}

int test_lvalue_rvalue_refrence_main() {
	
    //getInt() = 20;      //error: lvalue required as left operand of assignment
    //(setInt()) = 20;    //error: lvalue required as left operand of assignment
    *(setInt()) = 20;   // OK
    int i = getInt();   // OK

    //x is lvalue
	int x = 10;
	
	//ref is l-value reference
	int &ref = x ;
	
	//Transform returns an l-value
	int &ref2 = Transform(x) ;
	//int &&ref3 = Transform(x) ; // Error: OK, but not recommended, as it binds to l-value reference
	
	//Binds to function that accepts l-value reference
	//int &&ref3 = Transform(std::move(x)) ; // Error: an rvalue reference cannot be bound to an lvalue
	
	//Binds to function that accepts l-value reference
	int &ref3 = Transform(std::move(x)) ;
	int &ref4 = ref3; // OK, ref4 is an l-value reference to the same object as ref3
	
	//Binds to function that accepts l-value reference
	Print(x);
	
	//Binds to function that accepts const l-value reference
	const int n =20;
	Print(n);

	//rv is r-value reference
	int &&rv = 8 ;
	
	//Add returns a temporary (r-value)
	int &&rv2 = Add(3,5) ;
	
	//Binds to function that accepts a temporary, i.e. r-value reference
	Print(3);
	
	return 0;
}
#include <stdio.h>
#include <iostream>
class Base { public:Base(){};virtual ~Base(){};};
class Derived : public Base {
	public:
	Derived(){};
	~Derived(){};
	int code(){
		std::cout << "I code\n";
		return 0;
	}
};
class Derived1 : public Base {
	public:
	Derived1(){};
	~Derived1(){};
	int code(){
		std::cout << "I code\n";
		return 0;
	}
};
class Derived2 : public Base {
	public:
	Derived2(){};
	~Derived2(){};
	int code(){
		std::cout << "I code\n";
		return 0;
	}
};

int main(void)
{
	Derived1 b0;
	Base &b = b0;


	try {
		Derived2 d2 = dynamic_cast<Derived2&>(b);
		std::cout << &d2 << '\n';
		Derived d = dynamic_cast<Derived&>(b);
		std::cout << &d << '\n';
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	Derived1 d1 = dynamic_cast<Derived1&>(b);
	d1.code();
	
}


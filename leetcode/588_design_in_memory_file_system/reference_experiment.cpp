#include <iostream>

class TestClass{
public:
	TestClass(int _val) : val(_val) {printf("Constructor(%d)!\n", val);}
	~TestClass(){printf("Destructor(%d)!\n",val);}
private:
	int val;
};

TestClass& return_reference(){
	TestClass& ret = *(new TestClass(-1));
	return ret;
}

int main(){
	TestClass a1(1);
	TestClass a2(2);
	TestClass a3 = return_reference();
	TestClass a4(4);
	return 0;
};

// output:
// Constructor(1)!
// Constructor(2)!
// Constructor(-1)!
// Constructor(4)!
// Destructor(4)!
// Destructor(-1)!
// Destructor(2)!
// Destructor(1)!
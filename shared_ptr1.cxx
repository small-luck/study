//循环引用
#include <iostream>
#include <memory>
class B;
class A {
	public:
		std::shared_ptr<B> ptr;
};

class B {
	public:
		std::shared_ptr<A> ptr;
};

int main(int argc, const char *argv[])
{
	std::shared_ptr<A> pa(new A());
	std::shared_ptr<B> pb(new B());

	pa->ptr = pb;
	pb->ptr = pa;

	std::cout << "use_count = " << pa.use_count() << std::endl;
	std::cout << "use_count = " << pb.use_count() << std::endl;

	return 0;
}

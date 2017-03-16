


#include <iostream>
#include <exception>
struct T3{
	~T3()noexcept(false){
		std::cout<<"~T3\n";
		std::cout<<std::uncaught_exceptions()<<'\n';
	}

};

struct T2{
	~T2()noexcept(false){
		std::cout<<"~T2\n";
		std::cout<<std::uncaught_exceptions()<<'\n';
		throw 1;
	}

};

struct T1{
	~T1()noexcept(false){
		try{
			{T3 t3_;T2 t2_;}
			std::cout<<"you cannot see me\n";
		}catch(...){
			std::cout<<"~T1\n";
			std::cout<<std::uncaught_exceptions()<<'\n';
		}
	}
};

int main(void){

	try{
		T1 t_;
		std::cout<<std::uncaught_exceptions()<<'\n';
		std::cout<<"I'm about to throw\n";
		throw 0;
		std::cout<<"you cannot see me\n";
	}catch(...){
		std::cout<<std::uncaught_exceptions()<<'\n';
	}
	std::cout<<"done\n";
}



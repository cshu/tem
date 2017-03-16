#include <iostream>

int main(void){
	static_assert(std::is_same<decltype(0),int>::value,"");
	static_assert(std::is_same<decltype(2147483647),int>::value,"");
	static_assert(std::is_same<decltype(2147483648),long long>::value,"");//msvc bug, type is unsigned long
	static_assert(std::is_same<decltype(3147483648),long long>::value,"");//msvc bug, type is unsigned long
	static_assert(std::is_same<decltype(4294967295),long long>::value,"");//msvc bug, type is unsigned long
	static_assert(std::is_same<decltype(4294967296),long long>::value,"");
	static_assert(std::is_same<decltype(5294967296),long long>::value,"");
	static_assert(std::is_same<decltype(9223372036854775807),long long>::value,"");
	static_assert(std::is_same<decltype(9223372036854775808u),unsigned long long>::value,"");
	static_assert(std::is_same<decltype(10223372036854775808u),unsigned long long>::value,"");
	static_assert(std::is_same<decltype(18446744073709551615u),unsigned long long>::value,"");
	static_assert(std::is_same<decltype(18446744073709551616.0),double>::value,"");

}

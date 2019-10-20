

#include <type_traits>
#include <cassert>

int main(void){
	const char *pc="ex";
	const auto cco=pc;
	const auto *cpco=pc;
	auto *pco=pc;
	auto co=pc;
	const char c=0x41;
	auto co_c=c;
	static_assert(std::is_same<decltype(cco),const char * const>::value,"st");
	static_assert(std::is_same<decltype(cpco),const char *>::value,"st");
	static_assert(std::is_same<decltype(pco),const char *>::value,"st");
	static_assert(std::is_same<decltype(co),const char *>::value,"st");
	assert(co==pco);
	static_assert(std::is_same<decltype(co_c),char>::value,"st");
	char *pch=nullptr;
	const auto ccho=pch;
	const auto *cpcho=pch;
	static_assert(std::is_same<decltype(ccho),char * const>::value,"st");
	static_assert(std::is_same<decltype(cpcho),const char *>::value,"st");
}

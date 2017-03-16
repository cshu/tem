#include <vector>
#include <iostream>
 
int main()
{
	std::vector<char> vb;
	vb.resize(100);
	std::cout<<vb.capacity()<<'\n';

	vb.assign(1, 0);
	std::cout<<vb.capacity()<<'\n';//capacity doesn't change!
}

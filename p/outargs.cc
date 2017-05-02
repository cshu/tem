#include <iostream>

int main(int argc, char *argv[])
{
	for(--argc;argc>=0;--argc){
		std::cout<<argv[argc]<<"\n\n";
	}
}

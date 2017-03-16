#include <time.h>
#include <stdio.h>

#include <iostream>
#include <chrono>
#include <thread>

int main(void){
	using namespace std::chrono_literals;
	time_t t = time(NULL);
	std::this_thread::sleep_for(2s);
	double dif = difftime(time(NULL),t);
	printf("%f\n",dif);
	if(dif<3.0)puts("<");
	if(dif>1.0)puts(">");
	if(dif<1.0)puts("1");
	if(dif>3.0)puts("2");


}


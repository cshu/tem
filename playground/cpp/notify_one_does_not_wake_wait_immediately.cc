//output could be "db m" OR "m db"

#define IS_NIL(x) (x==NULL)


#include <cstdlib>
#include <thread>
#include <condition_variable>
#include <iostream>

using namespace std;

unsigned char *reqdt;
std::mutex dbmutex;
std::condition_variable dbcv;
bool db_ready;
void db(void){
		{
			std::unique_lock<std::mutex> ul(dbmutex);
			while(!db_ready)
				dbcv.wait(ul);
			std::cout<<"db"<<std::endl;
		}
}
int main(void){
thread dbthre{db};


		{
    std::this_thread::sleep_for(std::chrono::seconds(1));
			std::lock_guard<std::mutex> lgph(dbmutex);
			db_ready=true;
		}

		dbcv.notify_one();
    std::this_thread::sleep_for(std::chrono::microseconds(999));
    for(unsigned i=2000;i;--i);
		{
			std::lock_guard<std::mutex> lgph(dbmutex);
			std::cout<<"m"<<std::endl;
		}
dbthre.join();
}

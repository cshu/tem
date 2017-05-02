
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#define NO_NEED_TO_AVERT_RACES
#include <cpprs.h>

using namespace std;
int main(int argc, char **argv){
	try{
#define BUFSI 0x1000
#define MAXLENOFSE 0x200
		if(argc<3)return 1;
		if(!argv[1])return 1;
		auto lenofse=stoul(argv[1]);
		if(lenofse<2||lenofse>=MAXLENOFSE)return 1;
		auto fsi=getfilesizeusingifstream(argv[2]);
		//static_assert(std::is_same<decltype(fsi), long long>::value,"");
		if(fsi<BUFSI)return 1;
		cout<<"file size:"<<fsi<<'\n';
		uintmax_t threshold=5;
		if(lenofse<=3){//when lenofse is gt 3 nth power is too big...
			//for random data (maximum entropy), the expected frequency of the sequence
			auto expectedfrequency=(fsi-lenofse+1)/nthpowerof<>(0x100,lenofse);//fixme this is wrong! actual probability is lower than this! unless the sequence consists of same character!
			if(expectedfrequency)threshold=expectedfrequency*20;
		}
		cout<<"threshold:"<<threshold<<'\n';
		unique_ptr<char[]> sebuf(new char[lenofse]);
		unique_ptr<char[]> chbuf(new char[BUFSI]);
		//size_t lastscanlen;
		ifstream ifstre_(argv[2],ios_base::binary);//undone add support for more files
		if(!ifstre_){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
		auto sese=sebuf.get();
		auto reloc=chbuf.get();
		auto endloc=reloc+BUFSI;
		for(ifstream::off_type nextseoff=0;;){
			size_t counter=0;
			if(!ifstre_.read(sese,lenofse)){
				if(!ifstre_.eof()){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
				break;
			}
			if(!ifstre_.seekg(0,ios::beg)){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
			if(!ifstre_.read(reloc,BUFSI)){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
			auto cofsi=fsi-BUFSI;
			for(;;){
				char *res;
				startofmemmem:
				UNSAFE_MEMMEMs(res,reloc,endloc-reloc,sese,lenofse,{},{
					++counter;
					reloc=res;
					if(endloc-reloc>=lenofse)
						goto startofmemmem;
				})
				reloc=chbuf.get();
				if(!cofsi)break;
				memcpy(reloc,endloc-lenofse+1,lenofse-1);
				if(cofsi<BUFSI-(lenofse-1)){
					if(!ifstre_.read(reloc+lenofse-1,cofsi)){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
					cofsi=0;
				}else{
					if(!ifstre_.read(reloc+lenofse-1,BUFSI-(lenofse-1))){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
					cofsi-=BUFSI-(lenofse-1);
				}
			}
			if(counter>threshold){
				//todo this prints same sequence multiple times, you should use a set to store them, print each sequence only once
				cout<<strstrehexsetfillwrite(sese,lenofse).rdbuf()<<' '<<counter<<'\n';//note to read from rdbuf, you cannot use ostringstream
			}
			++nextseoff;
			if(!ifstre_.seekg(nextseoff,ios::beg)){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
		}
		ifstre_.clear(); ifstre_.close();
		if(!ifstre_){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
		return 0;
	}catch(const std::exception &e){
		clog<<e.what();
	}catch(...){
		clog<<"Uncaught Err\n";
	}
	return 1;
}

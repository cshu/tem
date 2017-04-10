
//undone Apart from single byte, all other entries are associated with deductions (deduction of frequency given another entry is used in encoding, e.g. abcab can be encoded to <ab>c<ab> and frequency of <bc> drops from 1 to 0.


#include <fstream>
#include <iostream>
#include <cmath>//? can be removed?
#include <memory>
#define XSTR(s) STR(s)
#define STR(s) #s

using namespace std;
int main(int argc, char **argv){
	try{
		if(argc<3)return 1;
		if(!argv[1])return 1;
		unsigned char mlenofentry=(unsigned char)argv[1][0]-0x30;
		if(!mlenofentry)return 1;
		//if(mlenofentry>7)return 1;
		if(mlenofentry>3)return 1;//impractical to allocate more
		size_t numofentries=0;
		for(size_t nthpowofbase=0x100,i=1;;nthpowofbase*=0x100){
			numofentries+=nthpowofbase;
			if(i==mlenofentry)break;
			++i;
		}
#define BUFSI 0x1000
#define SAFEMARGIN 0x10
		unique_ptr<char[]> chbuf(new char[BUFSI]);
		auto urec=make_unique<uint64_t[][2]>(numofentries);//first uint64_t for counting, second uint64_t for storing sequence when sorting
		//auto rec=new uint64_t[numofentries][2];
		auto rec=urec.get();
		size_t indofp=2;
		do{
			size_t lastscanlen;
			ifstream ifstre_(argv[indofp],ios_base::binary);
			if(!ifstre_){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
			auto reloc=chbuf.get();
			if(!ifstre_.read(reloc,BUFSI)){
				if(!ifstre_.eof()){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
				lastscanlen=ifstre_.gcount();
				goto scanlastbuf;
			}
			for(;;){
				for(size_t i=1;;++i){
					switch(mlenofentry){
					case 3:
						++rec[0x10100+reloc[0]+(size_t)(unsigned char)reloc[1]*0x100+(size_t)(unsigned char)reloc[2]*0x10000][0];
					case 2:
						++rec[0x100+reloc[0]+(size_t)(unsigned char)reloc[1]*0x100][0];
					case 1:
						++rec[(unsigned char)reloc[0]][0];
						break;
					}
					++reloc;
					if(i==BUFSI-SAFEMARGIN)break;
				}
				reloc=(decltype(reloc))memcpy(chbuf.get(),reloc,SAFEMARGIN);
				if(!ifstre_.read(chbuf.get()+SAFEMARGIN,BUFSI-SAFEMARGIN)){
					if(!ifstre_.eof()){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
					lastscanlen=SAFEMARGIN+ifstre_.gcount();
					goto scanlastbuf;
				}
			}
			scanlastbuf:
			ifstre_.clear(); ifstre_.close();
			if(!ifstre_){clog<<"ERROR AT LINE " XSTR(__LINE__) "\n"; throw 0;}
			for(size_t i=0;i!=lastscanlen;++i){
				switch(mlenofentry){
				case 3:
					if(i+2<lastscanlen)++rec[0x10100+reloc[0]+(size_t)(unsigned char)reloc[1]*0x100+(size_t)(unsigned char)reloc[2]*0x10000][0];//optimize
				case 2:
					if(i+1<lastscanlen)++rec[0x100+reloc[0]+(size_t)(unsigned char)reloc[1]*0x100][0];
				case 1:
					++rec[(unsigned char)reloc[0]][0];
					break;
				}
				++reloc;
			}
			++indofp;
		}while(argv[indofp]);
		//output
		for(size_t i=0;i<numofentries;++i){
			if(i==0x100)cout<<'\n';//undone
			if(i==0x10100)cout<<'\n';//undone
			cout<<rec[i][0]<<'\n';
		}
		return 0;
	}catch(const std::exception &e){
		clog<<e.what();
	}catch(...){
		clog<<"Uncaught Err\n";
	}
	return 1;
}

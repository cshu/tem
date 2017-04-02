
int main(void){
	switch(1){
		case 1:break;
		{case 2:{break;}}//might be counterintuitive, but compiles
		case 3:break;
	}
}

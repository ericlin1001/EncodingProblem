#include<iostream>
using namespace std;

//
typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned int dword;
typedef signed int sdword;
//

enum MyType{TYPE_UNKNOW,TYPE_BYTE,TYPE_SBYTE,TYPE_DWORD,TYPE_SDWORD};
template<class T>
MyType getType(const T t){return TYPE_UNKNOW;}
MyType getType(const dword t){return TYPE_DWORD;}
MyType getType(const sdword t){return TYPE_SDWORD;}
MyType getType(const byte t){return TYPE_BYTE;}
MyType getType(const sbyte t){return TYPE_SBYTE;}

template <class T>
const char *getTypeName(const T t){
	switch(getType(t)){
		default:
		case TYPE_UNKNOW:
			return "Unknow";
		case TYPE_BYTE:
			return "Unsigned Byte";
		case TYPE_SBYTE:
			return "Signed Byte\t";
		case TYPE_DWORD:
			return "Unsigned Double Word";
		case TYPE_SDWORD:
			return "Signed Double Word";
	};
}
template<class T>
bool getByte(const T b,int i){
	unsigned long k=1;
	k<<=i;
	return (b&k)==k;
	//return ((b>>i)&0x1)==0x1;
}
//
template <class T>
inline void _printB(const T t,int numBits){
	//like a memory [high ... low]
	//print from high address bits, to low address bits.
	for(int i=numBits-1;i>=0;i--){
		cout<<getByte(t,i);
	}
}

template <class T>
inline void printB(const T t,int numBits=-1){
	if(numBits==-1){
		if(getType(t)==TYPE_BYTE||getType(t)==TYPE_SBYTE){
			numBits=8;
		}else{
			numBits=32;
		}
	}
	_printB(t,numBits);
}

template<class T>
void printT(const T t){
	if(getType(t)==TYPE_BYTE||getType(t)==TYPE_SBYTE){
		cout<<(int)t;
	}else{
		cout<<t;
	}
}
//
template<class T>
void testType(T t){
#define print(m) cout<<#m"\t";printT(m);cout<<"\t";printB(m);cout<<endl;
	byte b=t;
	sbyte sb=t;
	dword dw=t;
	sdword sdw=t;
#define ToWhat(v) cout<<"To "<<getTypeName(v)<<"\t";print(v);
	ToWhat(b);
	ToWhat(sb);
	ToWhat(dw);
	ToWhat(sdw);
	cout<<endl;
}
void testAllType(){
#define ShowTest(v,cmd) cmd;\
	cout<<"After run command:"#cmd""<<endl;\
	cout<<"From "<<getTypeName(v)<<"\t";print(v);\
	cout<<"---"<<endl;\
	testType(v);cout<<endl;

#define ShowTests(v)  \
	ShowTest(v,v=128);\
	ShowTest(v,v=127);\
	ShowTest(v,v++);\
	ShowTest(v,v++);\
	ShowTest(v,v=-1);\
	ShowTest(v,v--);\
	ShowTest(v,v=0xffffff00+64);\

	byte b;
	sbyte sb;
	dword dw;
	sdword sdw;
	//
	ShowTests(b);
	ShowTests(sb);
	ShowTests(dw);
	ShowTests(sdw);
	//
}
int main(){
	testAllType();
	return 0;
}

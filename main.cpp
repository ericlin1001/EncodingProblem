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


char toHex(int a){
	if(a>=0&&a<=9){
		return '0'+a;
	}
	a-=10;
	return 'A'+a;
}
template<class T>
void printHex(T t,int numBytes=-1){
	byte x=0xf;
	cout<<"0x";
	//
	if(numBytes==-1){
		if(getType(t)==TYPE_BYTE||getType(t)==TYPE_SBYTE){
			numBytes=1;
		}else{
			numBytes=4;
		}
	}
	int b=numBytes*2;
	for(int i=0;i<b;i++){
		cout<<toHex((t>>4*(b-1-i))&x);
	}
}
void printAddr(void *t){
	//dword d=(dword)t;
	unsigned long d=(unsigned long)t;
	printHex(d);
}
void unicodeToUtf8(byte*from,int size,byte*to){
}

int main(){
//	testAllType();
	dword dw=0x0f0f0ff0;
	if ((*((byte*)&dw))==0xf0){
		cout<<"little-endian:least significant bit goes first, in lowest address"<<endl;
	}else if ((*((byte*)&dw))==0x0f){
		cout<<"big-endian:most significant bit goes first, in lowest address"<<endl;
	}else{
		cout<<"Uknown-endian, or Error"<<endl;
	}
	//
	cout<<"[";printAddr(&dw);cout<<"]:";printHex(dw);cout<<"\t";printB(dw);cout<<endl;
	byte *p;
	p=(byte*)&dw;
#define TT(v) cout<<"[";printAddr(v);cout<<"]:";printHex(*v);cout<<"\t";printB(*v);cout<<endl;v++;
	TT(p);
	TT(p);
	TT(p);
	TT(p);
	return 0;
}

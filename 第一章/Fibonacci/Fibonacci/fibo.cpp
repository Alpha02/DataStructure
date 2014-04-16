#include <iostream>
#include <fstream>
using namespace std;
long long known[100];
long long F(int n){
	if(n<0)return -1;
	if(!known[n]){
		known[n]=F(n-1)+F(n-2);
	}
	return known[n];
}
int getInput(){
	ifstream fin("input.txt");
	char str[100];
	int num=0;
	fin.getline(str,100);
	for(int i=0;str[i]>0;i++){
		if(str[i]<='9' && str[i] >='0'){
			num=num*10+str[i]-'0';
		}else{
			return -1;
		}
	}
	return num;
}
void output(long long n){
	if(n==-1){
		cout<<"WRONG"<<endl;
	}else{
		cout<<n<<endl;
	}
}
void main(){
	int n=getInput();
	int i;
	for(i=0;i<n;i++){
		known[i]=(i<=1);
	}
	output(F(n));
	system("PAUSE");
}
#include <iostream>
#include <fstream>
using namespace std;
bool element_chosen[26];
int max_number;
void OutputElements(){
	for(int i=0;i<max_number;i++){
		if(element_chosen[i]){
			cout<<(char)('a'+i)<<' ';
		}
	}
	cout<<endl;
}
void getSubset(int idx){

	for(int i=idx;i<max_number;i++){
		element_chosen[i]=true;
		OutputElements();
		getSubset(i+1);
		element_chosen[i]=false;
	}	
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
	if(num>26)return -1;
	return num;
}
int main(){
	max_number=getInput();

	if(max_number==-1){
		cout<<"WRONG"<<endl;
	}else{
		for(int i=0;i<max_number;i++){
			element_chosen[i]=false;
		}
		getSubset(0);
	}
	system("PAUSE");
	return 0;
}
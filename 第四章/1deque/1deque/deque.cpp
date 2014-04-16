#include <iostream>
#include <fstream>
#include<string.h>
using namespace std;
char cmd_list[][20]={
	"AddLeft","AddRight",
	"DeleteLeft","DeleteRight",
	"Left","Right",
	"IsFull","IsEmpty","End","Print"
	};
#define OP_END 8
class NoMem{};
class Empty{};
class deque{
private:
	int * list;
	int max_length;
	int id_left,id_right;
	bool full;
public:

	void Create(int len){
		max_length=len;
		list=new int[max_length];
		id_left=0;
		id_right=1;
		full=0;
	}
	deque(int len=10){
		Create(len);
	}
	bool IsEmpty(){
		if((id_left+1)%max_length==id_right)return 1;
		return 0;
	}
	bool IsFull(){
		return full;
	}
	int Left(){
		return list[(id_left+1)%max_length];
	}
	bool shiftLeft(){
		id_left--;
		if(id_left<0)id_left+=max_length;
		if(id_right==id_left)full=true;
	}
	bool shiftRight(){
		id_right++;
		if(id_right>=max_length)id_right-=max_length;
		if(id_right==id_left)full=true;
	}
	int Right(){
		return list[(id_right-1+max_length)%max_length];
	}
	void shift(int & id,int d){
		id=(id+d+max_length)%max_length;
	}
	void AddLeft(int new_int){
		if(full)throw NoMem();
		list[id_left]=new_int;
		shift(id_left,-1);
		if(id_right==id_left)full=true;
	}
	void AddRight(int new_int){
		if(full)throw NoMem();
		list[id_right]=new_int;
		shift(id_right,1);
		if(id_right==id_left)full=true;
	}
	void DeleteLeft(){
		if(IsEmpty())throw Empty();
		shift(id_left,1);
		full=false;
	}
	void DeleteRight(){
		if(IsEmpty())throw Empty();
		shift(id_right,-1);
		full=false;
	}
	void Print(){
		int id_temp=id_left;
		for(shift(id_temp,1);id_temp!=id_right;shift(id_temp,1)){
			cout<<list[id_temp]<<" ";
		}
		cout<<endl;
	}

};
int cmdcmp(char * str){
	int sz=sizeof(cmd_list)/sizeof(*cmd_list);
	for(int i=0;i<sz;i++){
		if(strcmp(cmd_list[i],str)==0){
			return i;
		}
	}
	return -1;
}
void PrintBool(bool b){
	if(b)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
}
int readCommand(istream & in,deque & dq){
	char op_code[20];
	int op_num;
	in>>op_code;
	int op_id=cmdcmp(op_code);

	try{
		switch(op_id){
		case 0:in>>op_num;dq.AddLeft(op_num);dq.Print();break;
		case 1:in>>op_num;dq.AddRight(op_num);dq.Print();break;
		case 2:dq.DeleteLeft();dq.Print();break;
		case 3:dq.DeleteRight();dq.Print();break;
		case 4:cout<<dq.Left()<<endl;break;
		case 5:cout<<dq.Right()<<endl;break;
		case 6:PrintBool(dq.IsFull());break;
		case 7:PrintBool(dq.IsEmpty());break;
		case 8:cout<<"Program Terminated"<<endl;break;
		case 9:dq.Print();break;
		default:cout<<"WRONG"<<endl;break;
		}
	}catch(NoMem){
		cout<<"FULL!"<<endl;
	}catch(Empty){
		cout<<"EMPTY!"<<endl;
	}
	return op_id;

}
int main(){
	deque dq(5);
	int op_id=1;
	while(op_id!=OP_END){
		op_id=readCommand(cin,dq);
	}
	system("PAUSE");
}
#include <iostream>
using namespace std;
class Circle{
protected:
	int length;
	int member_number;

public:
	virtual int popNext(int m)=0;
	void play(int m){
		while(popNext(m)>=0);
		cout<<endl;
	}
};
class CircleLinear : public Circle{
private:
	int * members;
	int current_id;
public:
	CircleLinear(int len){
		length=len;
		members=new int[len];
		for(int i=0;i<length;i++){
			members[i]=i;
		}
		member_number=len;
		current_id=0;
	}
	~CircleLinear(){
		delete []members;
	}
	int popMember(int id){
		int res=members[id];
		for(int i=id;i<member_number-1;i++){
			members[i]=members[i+1];
		}
		member_number--;
		if(id==member_number)id=0;
		cout<<res+1<<" ";
		return res;
	}
	int popNext(int m){
		if(!member_number)return -1;
		current_id=(current_id+m-1)%member_number;
		return popMember(current_id);
	}


};
class CircleLinked : public Circle{
private:
	struct circle_node{
		int idx;
		circle_node * next;
	}*head_node;
	circle_node* current_node;
public:
	CircleLinked(int len){
		length=len;
		head_node=new circle_node;
		circle_node * temp_node=head_node;
		for(int i=0;i<length;i++){
			temp_node->idx=i;
			if(i==length-1){
				temp_node->next=head_node;
				current_node=temp_node;
				break;
			}
			temp_node->next=new circle_node;
			temp_node=temp_node->next;
		}
		member_number=len;
	}
	~CircleLinked(){
		while(length--){
			circle_node * temp_node=head_node;
			head_node=head_node->next;
			delete temp_node;
			
		}
	}
	int popMember(circle_node * pre_node){
		circle_node * temp_node=pre_node->next;
		pre_node->next=pre_node->next->next;
		int res=temp_node->idx;
		delete temp_node;
		member_number--;
		cout<<res+1<<" ";
		return res;
	}
	virtual int popNext(int m){
		if(!member_number)return -1;
		while(--m){
			current_node=current_node->next;
		}
		return popMember(current_node);
	}
};
int main(){
	int n,m;
	int member_number;
	int current_id;
	cout<<"Input n,m;";
	cin>>n>>m;
	CircleLinear c1(n);
	c1.play(m);
	CircleLinked c2(n);
	c2.play(m);
	system("PAUSE");
	return 0;
}
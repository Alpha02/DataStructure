#include <iostream>
using namespace std;
class OutOfBounds{};
class NoMem{};
template <class T>
class Stack{
public:
	Stack(int MaxStackSize=10){
		MaxTop=MaxStackSize-1;
		stack= new T[MaxStackSize];
		top=-1;
	}
	~Stack(){delete[]stack;}
	bool isEmpty()const{return top==-1;}
	bool isFull()const{return top==MaxTop;}
	T Top()const{
		if(isEmpty())throw OutOfBounds();
		else return stack[top];
	}
	Stack<T> & Push(const T & x){
		if(isFull())throw NoMem();
		stack[++top]=x;
		return * this;
	}
	Stack<T> & Pop(T & x){
		if(isEmpty())throw OutOfBounds();
		x=stack[top--];
		return * this;
	}
	void Output(){
		for(int i=0;i<=top;i++){
			cout<<stack[i]<<' ';
		}
		cout<<endl;
	}
private:
	int top;
	int MaxTop;
	T * stack;
};
template <class T>
void delete_all(Stack<T> &s, const T &x){
	Stack <T> s2(10000);
	T temp;
	while(!s.isEmpty()){
		s.Pop(temp);
		if(temp!=x){
			s2.Push(temp);
		}
	}
	while(!s2.isEmpty()){
		s2.Pop(temp);
		s.Push(temp);
	}
}
void fill_stack(Stack<char> &s){
	char str[100];
	cin.getline(str,100);
	cin.getline(str,100);
	for(int i=0;str[i];i++){
		if(str[i]!=' '){
			s.Push(str[i]);
		}
	}
}
int main(){
	char a;
	cin>>a;
	Stack<char> s(100);
	fill_stack(s);
	delete_all(s,a);
	s.Output();
	system("PAUSE");
}
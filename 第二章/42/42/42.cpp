#include <iostream>
#include <iomanip>
using namespace std;
class OutOfBounds{};
template <class T>
class Term{
public:
	int row,col;
	T value;
	Term * next;
	Term(int r,int c,T v){
		row=r;
		col=c;
		value=v;
		next=NULL;
	}
	~Term(){
		if(next){
			delete(next);
		}
	}
	bool IndexLargerThan(Term & term2){
		if(row>term2.row)return true;
		if(col>term2.col)return true;
		return false;
	}
	bool locate(int r,int c){
		if(row!=r)return false;
		if(col!=c)return false;
		return true;
	}
};
template<class T>
class SparseMatrix{
private:
	int rows,cols;
	Term<T> * head;
public:
	SparseMatrix(int r=5,int c=5){
		rows=r;
		cols=c;
		head=NULL;
	}
	~SparseMatrix(){delete head;};
	void insert(Term<T> * new_term,Term<T>*term1,Term<T>*term2){
		new_term->next=term2;
		term1->next=new_term;
	}
	void Store(T new_t,int row,int col){
		
		Term<T> * new_term=new Term<T>(row,col,new_t);
		Term<T> * t=head;			
		if((!t)||(t->IndexLargerThan(*new_term))){
			new_term->next=t;
			head=new_term;
		}else{
			while(t){

				Term<T> * t2=t->next;
				if(!t2){
					t->next=new_term;
					break;
				}
				if(t2 && t2->IndexLargerThan(*new_term)){
					insert(new_term,t,t2);
					break;
				}
				t=t->next;
			}
		}
			
	}
	T Retrieve(int row,int col){
		if(row<1 || row>rows || col<1 || col>cols)throw OutOfBounds();
		Term<T> * t=head;
		while(t){
			if(t->locate(row,col)){
				return t->value;
			}else{
				t=t->next;
			}
		}
		return 0;
	}
	void input(){
		cout<<"input [rows,cols,value]=";
		int r,c;
		T v;
		
		cin>>r;
		while(r>0){
			cin>>c>>v;
			Store(v,r,c);
			cout<<"input [rows,cols,value]=";
			cin>>r;
		}
	}
	void Output(){
		for(int i=1;i<=rows;i++){
			for(int j=1;j<=cols;j++){
				cout<<setw(3)<<Retrieve(i,j);
			}
			cout<<endl;
		}
	}

};
int main(){
	SparseMatrix<int> sMat;
	sMat.input();
	sMat.Output();
	system("PAUSE");
}
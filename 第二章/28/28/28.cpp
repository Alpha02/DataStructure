#include <iostream>
#include <iomanip>
using namespace std;
class OutOfBounds{
};
template <class T>
class CMatrix{
private:
	int n;
	T * t;
public:
	CMatrix(int size=3){
		n=size;
		t=new T[3*n-2];
	}
	int getID(int i,int j){
		if(i<1 || i>n || j<1 || j>n)throw OutOfBounds();
		if(	i== 1)return j-1;
		if(i==n)return j+n-1;
		if(j==1)return 2*n+i-2;
		return -1;
	}
	T Retrieve(int i,int j){
		int id=getID(i,j);
		if(id==-1)return 0;
		return t[id];
	}
	void Store(T val,int i,int j){
		T[getID(i,j)]=val;
	}
	void Input(){
		cout<<"Please input the "<<3*n-2<<" elements of CMatrix:\n";
		for(int i=0;i<3*n-2;i++){
			cin>>t[i];
		}
	}
	void Output(){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cout<<setw(3)<<Retrieve(i,j);
			}
			cout<<endl;

		}
	}
};
int main(){
	int size;
	cout<<"Please input the SIZE:";
	cin>>size;
	CMatrix<int> mat(size);
	mat.Input();
	mat.Output();
	while(1){
		cout<<"[i,j]=";
		int i,j;
		cin>>i>>j;
		try{
		cout<<mat.Retrieve(i,j)<<endl;
		}catch(OutOfBounds){
			cout<<"Error:OutOfBounds"<<endl;
		}
	}
}
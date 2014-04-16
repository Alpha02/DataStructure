#include<iostream>
#include <iomanip>
using namespace std;
class OutOfBounds{
};
class MustBeZero{
};
class MatrixSizeMismatch{

};
template <class T>
class TriByCols
{
public:
	TriByCols(int size=10){
		n=size;
		t=new T [3*n-2];
	}
	~TriByCols(){
		delete []t;
	}
	TriByCols& Store(const int&x,int i,int j);
	T Retrieve(int i,int j)const;
	int Search(T target);
	TriByCols<T>& Plus(TriByCols& mat2);
	TriByCols<T>& Minus(TriByCols& mat2);
	TriByCols<T>& Transform();
	void Input(){
		cout<<"please input the "<<3*n-2<<" elements of TriByCols"<<endl;
		for(int x=0;x<3*n-2;x++){
			cin>>t[x];
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
private:
	int n;
	int *t;
};
template <class T>
TriByCols<T>& TriByCols<T>::Store(const int&x,int i,int j)
{
	if (i<1||j<1||i>n||j>n)throw OutOfBounds();
	t[2*j+i-3]=x;
	return * this;
}
template <class T>
T TriByCols<T>::Retrieve(int i,int j)const
{
	if (i<1||j<1||i>n||j>n)throw OutOfBounds();
	if (abs(i-j)>1)return 0;
	return t[2*j+i-3];
}
template <class T>
TriByCols<T>& TriByCols<T>::Plus(TriByCols& mat2)
{
	if(n!=mat2.n)throw MatrixSizeMismatch();
	TriByCols *mat_new=new TriByCols(n);
	for (int i=0;i<3*n-2;i++)(*mat_new).t[i]=t[i]+mat2.t[i];
	return *mat_new;
}
template <class T>
TriByCols<T>& TriByCols<T>::Minus(TriByCols& mat2)
{
	if(n!=mat2.n)throw MatrixSizeMismatch();
	TriByCols *mat_new=new TriByCols(n);
	for (int i=0;i<3*n-2;i++)(*mat_new).t[i]=t[i]-mat2.t[i];
	return *mat_new;
}
void swap(int x,int y)
{
	int k=x;x=y;y=k;
}
template <class T>
TriByCols<T>& TriByCols<T>::Transform(){
	TriByCols *mat_new=new TriByCols(n);
	for (int i=0;i<3*n-2;i+=1){
		
		if(i%3==1){
		(*mat_new).t[i]=t[i+1];
		(*mat_new).t[i+1]=t[i];
		}else if(i%3!=2){
			(*mat_new).t[i]=t[i];
		}
	}
	return *mat_new;
}
template <class T>
int TriByCols<T>::Search(T target){
	for (int x=0;x<3*n-2;x++)if(t[x]==target){
		int i=(x+1)%3+(x+1)/3;
		int j=(x+1)/3+1;
		cout<<"Found target in ["<<i<<","<<j<<"]\n";
		return x;
	}
	cout<<"Failed to find target\n";
	return -1;
}

void main()
{
	int n;
	cout<<"Please input the SIZE:";
	cin>>n;
	TriByCols<int> x(n);
	TriByCols<int> y(n);
	x.Input();
	x.Output();
	y.Input();
	y.Output();
	TriByCols<int> z(n);
	z=x.Plus(y);
	cout<<"X+Y=\n";
	z.Output();
	cout<<"X-Y=\n";
	z=x.Minus(y);
	cout<<"X'=\n";
	z=x.Transform();
	z.Output();
	while(1){
		int s;
		cout<<"Search->";
		cin>>s;
		x.Search(s);
	}

}


	


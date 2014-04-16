#include <iostream>
using namespace std;
class OutOfBounds{
};
class MustBeZero{
};
class MatrixSizeMismatch{
};
template <class T>
class DiagonalMatrix{
public:
	DiagonalMatrix(int size=10,bool isTemp=false){
		n=size;d=new T[n];
		TempMat=isTemp;
	}
	~DiagonalMatrix(){
		delete[] d;
	}
	DiagonalMatrix<T> & Store(const T & x,int i , int j);
	DiagonalMatrix<T> & Add(const T & x,int i , int j);
	DiagonalMatrix<T> & Reverse(int i , int j);
	DiagonalMatrix<T> & Transform(){
		return *this;

	}
	T Retrieve(int i, int j) const;
	void Input();
	void Output();
	bool isTempMat() const{
		return TempMat;
	}
	DiagonalMatrix<T> & operator +(const DiagonalMatrix<T> &Mat2){
		int maxsize=n;
		if(Mat2.n>n)maxsize=Mat2.n;
		DiagonalMatrix<T> *MatRes=new DiagonalMatrix<T>(maxsize,true);
		for(int i=0;i<maxsize;i++){
			MatRes->Store(0,i+1,i+1);
			if(n>i){
				MatRes->Add(d[i],i+1,i+1);
			}
			if(Mat2.n>i){
				MatRes->Add(Mat2.d[i],i+1,i+1);
			}
		}

		return *MatRes;
	}
	DiagonalMatrix<T> & operator -(const DiagonalMatrix<T> &Mat2){
		int maxsize=n;
		if(Mat2.n>n)maxsize=Mat2.n;
		DiagonalMatrix<T> *MatRes=new DiagonalMatrix<T>(maxsize,true);
		for(int i=0;i<maxsize;i++){
			MatRes->Store(0,i+1,i+1);
			if(n>i){
				MatRes->Add(d[i],i+1,i+1);
			}
			if(Mat2.n>i){
				MatRes->Add(-Mat2.d[i],i+1,i+1);
			}
		}

		return *MatRes;
	}
	DiagonalMatrix<T> & operator *(const DiagonalMatrix<T> &Mat2){
		int maxsize=n;
		if(Mat2.n!=n)throw MatrixSizeMismatch();
		DiagonalMatrix<T> *MatRes=new DiagonalMatrix<T>(maxsize,true);
		for(int i=0;i<maxsize;i++){
			MatRes->Store(d[i]*Mat2.d[i],i+1,i+1);
		}
		return *MatRes;
	}

private:
	int n;
	T * d;
	bool TempMat;
};	
template <class T>
ostream & operator << (ostream & out,DiagonalMatrix<T> &Mat2){
		Mat2.Output();
		return out;
}
template <class T>
istream & operator >> (istream & in,DiagonalMatrix<T> &Mat2){
	Mat2.Input();
	return in;
}
template <class T>
DiagonalMatrix <T> & DiagonalMatrix<T>::Store(const T & x,int i,int j){
	if(i<1|| j<1 || i>n || j>n)
		throw OutOfBounds();
	if(i!=j && x != 0 ) throw MustBeZero();
	if(i==j) d[i-1]=x;
	return * this;
}
template <class T>
DiagonalMatrix <T> & DiagonalMatrix<T>::Add(const T & x,int i,int j){
	if(i<1|| j<1 || i>n || j>n)
		throw OutOfBounds();
	if(i!=j && x != 0 ) throw MustBeZero();
	if(i==j) d[i-1]+=x;
	return * this;
}
template <class T>
DiagonalMatrix <T> & DiagonalMatrix<T>::Reverse(int i,int j){
	if(i<1|| j<1 || i>n || j>n)
		throw OutOfBounds();
	if(i!=j && x != 0 ) throw MustBeZero();
	if(i==j) d[i-1]=-d[i-1];
	return * this;
}
template <class T>
T DiagonalMatrix<T>::Retrieve(int i,int j) const{
	if(i<1 || j<1 || i>n || j>n)throw OutOfBounds();
	if(i==j) return d[i-1];
	else return 0;
}
template <class T>
void DiagonalMatrix<T>::Input(){
	cout<<"Please input the "<<n<<" elements in the DiagonalMatrix:"<<endl;
	for(int i=0;i<n;i++){
		cin>>d[i];
	}
}
template <class T>
void DiagonalMatrix<T>::Output(){
	cout<<"There are "<<n<<" elements in the DiagonalMatrix:"<<endl;
	for(int i=0;i<n;i++){
		cout<<d[i]<<" ";
	}
	cout<<endl;
}
int main(){
	DiagonalMatrix <int> diag1;
	DiagonalMatrix <int> diag2;
	DiagonalMatrix <int> diag3;
	cin>>diag1>>diag2;
	cout<<"A*B="<<(diag1*diag2)<<"\nA+B="<<(diag1+diag2)<<"\nA-B="<<diag1-diag2<<"A'="<<diag1.Transform();
	system("PAUSE");
	return 0;
}

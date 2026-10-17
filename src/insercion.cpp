#include<iostream>
using namespace std;

void Insercion(int A[], int n){
	for(int i=1;i<n;i++){
		int aux=A[i];
		int k=i-1;
		while( k>=0 && aux<A[k] ){
			A[k+1]=A[k];
			k=k-1;
		}
		A[k+1]=aux;
	}
}

int main(){
	int A[10]={8,2,3,9,1,3,8,5,3,8};
	int n=10;
	Insercion(A,n);
	for(int i=0;i<n;i++){
		cout<<A[i]<<" ";
	}
	return 0;
}
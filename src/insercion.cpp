#include<iostream>
using namespace std;
void Insercion(int A[], int n, long long &comparaciones, long long &intercambios){
	for(int i=1;i<n;i++){
		int aux=A[i];
		int k=i-1;
		while(k>=0){
			comparaciones++;        
			if(aux<A[k]){
				A[k+1]=A[k];
				intercambios++;    
				k=k-1;
			} else {
				break;             
			}
		}
		A[k+1]=aux;
			}
}

int main(){
	int A[10]={8 2 3 9 1 3 8 5 3 8};
	int n=10;
	long long comparaciones=0, intercambios=0;

	Insercion(A,n,comparaciones,intercambios);

	for(int i=0;i<n;i++){
		cout<<A[i]<<" ";
	}
	cout<<endl<<"Comparaciones: "<<comparaciones<<endl;
	cout<<"Intercambios: "<<intercambios<<endl;
	return 0;
}

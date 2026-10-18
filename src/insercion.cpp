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
void ShellSort(int A[], int n, long long &comparaciones, long long &intercambios){
	int k=n;
	while(k>1){
		k=k/2;                      
		for(int i=k;i<n;i++){
			int aux=A[i];
			int j=i;
			while(j-k>=0){
				comparaciones++;    
				if(A[j-k]>aux){
					A[j]=A[j-k];    
					intercambios++;
					j=j-k;
				} else {
					break;
				}
			}
			A[j]=aux;
		}
	}
}

int main(){
	int original[10]={2,3,7,5,7,9,5,3,2,1};
	int n=10;
	int a[10], b[10];
	
	for(int i=0;i<n;i++){
		a[i]=original[i];
		b[i]=original[i];
	}

	long long c1=0, i1=0, c2=0, i2=0;
	Insercion(a,n,c1,i1);
	ShellSort(b,n,c2,i2);

	cout<<"Inserción:  ";
	for(int i=0;i<n;i++) cout<<a[i]<<" ";
	cout<<endl<<"Comparaciones: "<<c1<<"  Intercambios: "<<i1<<endl<<endl;

	cout<<"Shell sort: ";
	for(int i=0;i<n;i++) cout<<b[i]<<" ";
	cout<<endl<<"Comparaciones: "<<c2<<"  Intercambios: "<<i2<<endl;
	return 0;
}

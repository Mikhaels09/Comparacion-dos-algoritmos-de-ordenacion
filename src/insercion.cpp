#include<iostream>
#include<cstdlib>   
#include<chrono>    
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


bool estaOrdenado(int A[], int n){
	for(int i=1;i<n;i++){
		if(A[i-1]>A[i]) return false;
	}
	return true;
}

int main(){
	int n=1000;                      
	int* original=new int[n];      
	int* copia=new int[n];           


	srand(12345);
	for(int i=0;i<n;i++){
		original[i]=rand()%32768;    
	}

//insercion
	for(int i=0;i<n;i++) copia[i]=original[i];  
	long long c1=0, i1=0;
	auto inicio1=chrono::steady_clock::now();    
	Insercion(copia,n,c1,i1);
	auto fin1=chrono::steady_clock::now();      
	double t1=chrono::duration<double,milli>(fin1-inicio1).count();   
	cout<<"Insercion -> tiempo: "<<t1<<" ms, comparaciones: "<<c1
	    <<", intercambios: "<<i1<<", ordenado: "<<estaOrdenado(copia,n)<<endl;

// shellsort
	for(int i=0;i<n;i++) copia[i]=original[i];   
	long long c2=0, i2=0;
	auto inicio2=chrono::steady_clock::now();
	ShellSort(copia,n,c2,i2);
	auto fin2=chrono::steady_clock::now();
	double t2=chrono::duration<double,milli>(fin2-inicio2).count();
	cout<<"ShellSort -> tiempo: "<<t2<<" ms, comparaciones: "<<c2
	    <<", intercambios: "<<i2<<", ordenado: "<<estaOrdenado(copia,n)<<endl;

	delete[] original;
	delete[] copia;
	return 0;
}

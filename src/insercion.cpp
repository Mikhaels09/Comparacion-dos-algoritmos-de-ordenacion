#include<iostream>
#include<string>
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

void generar(int A[], int n, string patron, unsigned int semilla){
	if(patron=="aleatorio"){
		srand(semilla);               
		for(int i=0;i<n;i++){
			A[i]=rand()%32768;         
		}
	} else if(patron=="ascendente"){
		for(int i=0;i<n;i++) A[i]=i;   
	} else {                          
		for(int i=0;i<n;i++) A[i]=n-i;  
	}
}

int main(){
	int n=1000;
	int* original=new int[n];
	int* copia=new int[n];
	string patrones[3]={"aleatorio","ascendente","descendente"};

	// Repito lo mismo para cada patrón
	for(int p=0;p<3;p++){
		generar(original,n,patrones[p],12345);
		cout<<"--- Patron: "<<patrones[p]<<" (n="<<n<<") ---"<<endl;

		//Inserción
		for(int i=0;i<n;i++) copia[i]=original[i];
		long long c1=0, i1=0;
		auto inicio1=chrono::steady_clock::now();
		Insercion(copia,n,c1,i1);
		auto fin1=chrono::steady_clock::now();
		double t1=chrono::duration<double,milli>(fin1-inicio1).count();
		cout<<"Insercion -> "<<t1<<" ms, comparaciones: "<<c1<<", intercambios: "<<i1
		    <<", ordenado: "<<estaOrdenado(copia,n)<<endl;

		//Shellsort
		for(int i=0;i<n;i++) copia[i]=original[i];
		long long c2=0, i2=0;
		auto inicio2=chrono::steady_clock::now();
		ShellSort(copia,n,c2,i2);
		auto fin2=chrono::steady_clock::now();
		double t2=chrono::duration<double,milli>(fin2-inicio2).count();
		cout<<"ShellSort -> "<<t2<<" ms, comparaciones: "<<c2<<", intercambios: "<<i2
		    <<", ordenado: "<<estaOrdenado(copia,n)<<endl<<endl;
	}

	delete[] original;
	delete[] copia;
	return 0;
}

#include<iostream>
#include<fstream>
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
 
bool estaOrdenado(int A[], int n){
	for(int i=1;i<n;i++){
		if(A[i-1]>A[i]) return false;
	}
	return true;
}
 
int main(int argc, char* argv[]){
	string commit="sin_commit";
	if(argc>1) commit=argv[1];
	bool incluirGrande=false;
	if(argc>2 && string(argv[2])=="grande") incluirGrande=true;
 
	int tamanos[3]={1000,10000,100000};
	int cantidadTamanos=2;                      
	if(incluirGrande) cantidadTamanos=3;
 
	string patrones[3]={"aleatorio","ascendente","descendente"};
	string algoritmos[2]={"Insercion","ShellSort"};
	int REPETICIONES=30;
	unsigned int SEMILLA_BASE=12345;
 
	ofstream csv("data/resultados.csv");
	csv<<"algoritmo,n,patron,repeticion,tiempo_ms,comparaciones,intercambios,profundidad_recursion,semilla,commit_hash"<<endl;
 
	for(int t=0;t<cantidadTamanos;t++){
		int n=tamanos[t];
		int* original=new int[n];       
		int* copia=new int[n];         
 
		for(int p=0;p<3;p++){
			for(int r=1;r<=REPETICIONES;r++){
				unsigned int semilla=SEMILLA_BASE+r;
				generar(original,n,patrones[p],semilla);
 
				for(int a=0;a<2;a++){
	
					for(int i=0;i<n;i++) copia[i]=original[i];
 
					long long comparaciones=0, intercambios=0;
 
				
					auto inicio=chrono::steady_clock::now();
			
					if(a==0) Insercion(copia,n,comparaciones,intercambios);
					else     ShellSort(copia,n,comparaciones,intercambios);
				
					auto fin=chrono::steady_clock::now();
 
					
					double tiempo_ms=chrono::duration<double,milli>(fin-inicio).count();
 
					
					if(!estaOrdenado(copia,n)){
						cout<<"ERROR: no quedo ordenado ("<<algoritmos[a]<<", n="<<n<<")"<<endl;
						return 1;
					}
 
				
					csv<<algoritmos[a]<<","<<n<<","<<patrones[p]<<","<<r<<","
					   <<tiempo_ms<<","<<comparaciones<<","<<intercambios<<",0,"
					   <<semilla<<","<<commit<<endl;
				}
			}
		}
		delete[] original;             
		delete[] copia;
		cout<<"Listo n = "<<n<<endl;
	}
		
	csv.close();
	cout<<"Resultados guardados en data/resultados.csv"<<endl;
	return 0;
}

//Author: Yunis Nabiyev
//CECS 325-02 Prog 0
//Due: 02/01/2024

#include <iostream>
using namespace std;

//Fibo Sequence
int fibo(int n){
	if(n == 1 || n == 0){
		return 1;
	}
	else{
		return fibo(n-1) + fibo(n-2); //recursive call
	}
}

int main(){
	for(int i = 0; i <= 20; i++){
		cout << i << ":" << fibo(i) << endl;
	}

	return 0;
}

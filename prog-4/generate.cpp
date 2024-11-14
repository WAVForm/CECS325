#include <fstream>
#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]){
    if(argc < 4 || argc > 4){
        throw std::invalid_argument("Invalid number of arguments: COUNT MIN MAX");
    }
    else{
	cout << "argv[0]:" << argv[0] << endl
	<< "argv[1]:" << argv[1] << endl
	<< "argv[2]:" << argv[2] << endl
	<< "argv[3]:" << argv[3] << endl;
        int COUNT = stoi(argv[1]);
        int MIN = stoi(argv[2]);
        int MAX = stoi(argv[3]);
        srand(time(0));
        ofstream numsFile("numbers.dat") ;
        for(int i=0; i<COUNT; i++){
            numsFile << (rand() % (MAX+1-MIN))+MIN << endl;
        }
        numsFile.close();
        return 0;
    }
}

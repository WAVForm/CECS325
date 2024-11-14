#include <fstream>
#include <iostream>
using namespace std;

void bubble(int A[], int size){
    cout << "Starting Array bubble sort with " << size << " items" << endl;
    for(int end = size; end > 0; end--){
        for(int i=0; i<end-1; i++){
            if(A[i] > A[i+1]){
                int temp = A[i];
                A[i] = A[i+1];
                A[i+1] = temp;
            }
        }
    }
    cout << "Ending bubble sort" << endl;
}

int main(int argc, char* argv[]){
    if(argc > 3 || argc < 3){
        throw std::invalid_argument("Invalid number of arguments: INPUT OUTPUT");
    }
    else{
	cout << "Starting my sort" << endl;
        fstream numsFile;
        numsFile.open((argv[1]));
        int numsCount = 0;
        string temp;
        while(getline(numsFile, temp)){
            numsCount++;
        }
        numsFile.close();
        numsFile.open(argv[1]);
        int nums[numsCount];
        for(int i=0; i<numsCount; i++){
            getline(numsFile, temp);
            nums[i] = stoi(temp);
        }
        numsFile.close();
        bubble(nums, numsCount);
        ofstream output;
        output.open(argv[2]);
        for(int i=0; i<numsCount; i++){
            output << to_string(nums[i])+"\n";
        }
        output.close();
    }
}

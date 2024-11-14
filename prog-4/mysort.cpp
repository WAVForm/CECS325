// Yunis Nabiyev
// Class (CECS 325-02)
// Project Name (Prog 4 – SortRace using pthreads)

// Due Date (03/26/2024)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

// I hereby also certify that I needlessly created the mergeSortTwoArrays() function without knowing std::merge() existed

#include <fstream>
#include <iostream>
#include <pthread.h>
#include <cmath> //for pow()
using namespace std;

struct arg_struct{
    int size;
    int *start;
};

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

void *bridge(void* ptr){
    arg_struct *arg = (arg_struct *) ptr;
    bubble(arg->start, arg->size);
}

void mergeSortTwoArrays(int a1[], int& a1size, int a2[], int& a2size){
    //merge a1 and a2, store new array in a1 and update size to be new larger size
    //a1 and a2 are already sorted
    int l = 0 , r= 0;
    int merged_size = (a1size+a2size);
    int *merged = new int [merged_size];

    for(int i = 0; i <(merged_size); i++){
        if(l >= a1size){
            merged[i] = a2[r];
            r++;
        }
        else if(r >= a2size){
            merged[i] = a1[l];
            l++;
        }
        else{
            if(a1[l] <= a2[r]){
                merged[i] = a1[l];
                l++;
            }
            else{
                merged[i] = a2[r];
                r++;
            }
        }
    }

    a1size = (merged_size);
    for (int i = 0; i < a1size; i++){
        a1[i] = merged[i];
    }
    delete[] merged;

}

int main(int argc, char* argv[]){
    if(argc > 3 || argc < 3){
        throw std::invalid_argument("Invalid number of arguments: INPUT OUTPUT");
    }
    else{
	cout << "Starting my sort" << endl;
        const int thread_count = 8; // make number which has only even factors
        fstream numsFile;
        numsFile.open((argv[1]));
        int numsCount = 0;
        string temp;
        while(getline(numsFile, temp)){
            numsCount++;
        }
        numsFile.close();
        numsFile.open(argv[1]);
        int* nums = new int[numsCount];
        for(int i=0; i<numsCount; i++){
            getline(numsFile, temp);
            nums[i] = stoi(temp);
        }
        numsFile.close();

        //The following code was written with the idea that possibly more or less than 8 threads may be used

        if(numsCount >= thread_count){
            arg_struct args[thread_count];
            for(int i = 0; i<thread_count; i++){
                if (i < thread_count-2){
                    args[i].size = numsCount/thread_count;
                }
                else{
                    args[i].size = (numsCount/thread_count) + (numsCount % thread_count);
                }
                args[i].start = &nums[(args[i].size * i)];
            }

            pthread_t threads[thread_count];
            for(int i = 0; i<thread_count; i++){
                int t = pthread_create(&threads[i], NULL, bridge, (void*) &args[i]);
            }
            for(int i = 0; i<thread_count; i++){
                int t = pthread_join(threads[i], NULL);
            }
            for(int i=0; i<(thread_count/2)-1; i++){
                for(int j=0; j<(thread_count/2)/(i+1); j++){
                    int l = j*pow(2,i+1);
                    int r = l + pow(2,i);
                    mergeSortTwoArrays(args[l].start, args[l].size, args[r].start, args[r].size);
                }
            }
            for(int i=0; i<args[0].size; i++){
                nums[i] = args[0].start[i];
            }
        }
        else{
            bubble(nums, numsCount);
        }
        
        ofstream output;
        output.open(argv[2]);
        for(int i=0; i<numsCount; i++){
            output << to_string(nums[i])+"\n";
        }
        output.close();
    }
}

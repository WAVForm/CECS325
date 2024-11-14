#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>

int globalSwapCount = 0;

class Bucket{
    private:
        std::vector<int> v;
    public:
        Bucket(){
            //what to put here?
        }
        void generate(int size, int min, int max){
            for(int i = 0; i < size; i++){
                v.push_back((rand() % (max+1-min))+min);
            }
        }
        void sort(){
            for(int end = size(); end > 0; end--){
                for(int i=0; i<end-1; i++){
                    if(v[i] > v[i+1]){
                        int temp = v[i];
                        v[i] = v[i+1];
                        v[i+1] = temp;
                        globalSwapCount++;
                    }
                }
            }
        }
        int size(){
            return v.size();
        }
        int atIndex(int index){
            return v[index];
        }
        void merge(Bucket b){
            int l = 0 , r= 0;
            int merged_size = (size()+b.size());
            int *merged = new int [merged_size];

            for(int i = 0; i <(merged_size); i++){
                if(l >= size()){
                    merged[i] = b.atIndex(r);
                    r++;
                }
                else if(r >= b.size()){
                    merged[i] = atIndex(l);
                    l++;
                }
                else{
                    if(atIndex(l) <= b.atIndex(r)){
                        merged[i] = atIndex(l);
                        l++;
                    }
                    else{
                        merged[i] = b.atIndex(r);
                        r++;
                    }
                }
            }

            v = std::vector<int>(merged, merged+merged_size);
            delete[] merged;
        }
};

int main(int argc, char *argv[]){
    std::srand(time(0));

    int bucketCount = std::stoi(argv[1]);
    int bucketSize = std::stoi(argv[2]);
    int bucketMin = std::stoi(argv[3]);
    int bucketMax = std::stoi(argv[4]);

    std::cout << "Bucket Count:"<<bucketCount<<std::endl;
    std::cout << "Bucket Size:"<<bucketSize<<std::endl;
    std::cout << "Bucket Min Value:"<<bucketMin<<std::endl;
    std::cout << "Bucket Max value:"<<bucketMax<<std::endl;
    
    std::vector<Bucket> list; // create empty Bucket vector
    
    Bucket *bptr;
    for(int i=0; i<bucketCount; i++){ // creating bucketCount Buckets
        bptr = new Bucket; // allocating new Bucket
        bptr->generate(bucketSize, bucketMin, bucketMax); //Bucket::generate(int,int,int)
        list.push_back(*bptr); // pushing Bucket onto list
    }

    for (auto it = list.begin(); it != list.end(); it++){
        it->sort(); // Bucket::sort
    }

    Bucket endGame; // create empty Bucket to merge ALL buckets

    while (list.size() > 0){ // vector<Bucket>::size()
        endGame.merge(list[0]); // merge first bucket in list into endGame
        list.erase(list.begin()); // erase the first bucket in the list
    }

    // write all the numbers in endGame bucket to a file
    std::fstream out("bucketList.out", std::ios::out);
    for(int i=0; i<endGame.size(); i++) // Bucket::size()
        out << endGame.atIndex(i) << std::endl; // Bucket::atIndex(int)
    std::cout << "Global Swap Count:"<< globalSwapCount <<std::endl;
    std::cout << "\nbucketList.out has "<<bucketCount * bucketSize << " sorted numbers\n";
    return 0;
}
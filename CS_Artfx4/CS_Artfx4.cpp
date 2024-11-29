#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>

std::array<std::array<int,5>,5> graph = {std::array<int,5>{0,2,2,0,0},std::array<int,5>{2,0,3,3,1},std::array<int,5>{2,3,0,1,3},std::array<int,5>{0,3,1,0,3},std::array<int,5>{0,1,3,3,0}};

struct Path{
    std::vector<int> path;
    int cost;
};

Path resolve(int start,std::array<bool,5> visit, int curr){
    visit[curr]=true;
    if(std::all_of(visit.begin(),visit.end(),[](bool i){return i;}) ){
        if(graph[curr][start]!=0)return {{curr,start},graph[curr][start]};
        else return {{curr},INT_MAX};
    }else{
        Path res={{},INT_MAX};
        for(int i=0;i<5;i++){
            if(graph[curr][i]!=0 && !visit[i]){
                Path res2 = resolve(start,visit,i);
                if (res2.cost!=INT_MAX && res2.cost+graph[curr][i]<res.cost){
                    res2.cost+=graph[curr][i];
                    res = res2;
                }
            }
        }
        res.path.insert(res.path.begin(),curr);
        return res;
    }
}

// 73%, doesn't work with large numbers https://app.codility.com/demo/results/trainingANBYC3-S7W/

int binaryGap(int N){
    int v = N; 
    int res = 0;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    if(v==N)return 0;
    else{
        v/=2;
        N-=v;
        int res2 = 0;
        v/=2;
        while(v>0){
            if(N<v){
                res2++;
            }else if (N==v){
                if(res2>res) return res2;
                else return res;
            }else{
                if(res2>res) res = res2;
                res2 = 0;
                N-=v;
            }
            v/=2;
        }
    }
}

// 44% float rounding errors on large numbers
/*int frogJMP(int X, int Y, int D) {
    return std::ceil(float(Y-X)/float(D));
}*/

//100% O(1), switched to doubles https://app.codility.com/demo/results/trainingKPH6GK-N3N/
int frogJMP(int X, int Y, int D) {
    return std::ceil(double(Y-X)/double(D));
}

//100% O(N) or O(N log N) https://app.codility.com/demo/results/training6A987P-Z8C/

int permMissingElem(std::vector<int> &A) {
    if(A.empty())return 1;
    std::sort(A.begin(),A.end());
    for(int i = 0; i<A.size();i++){
        if(A[i]!=i+1)return i+1;
    }
    return A.size()+1;
}

// 100% https://app.codility.com/demo/results/trainingSAE3UF-X46/
std::vector<int> cyclicRotation(std::vector<int> &A, int K) {
    if(A.empty())return A;
    std::vector<int> v = A;
    K = K % v.size();
    std::vector<int> res(v.end() - K, v.end());
    v.resize(v.size()-K);
    res.insert(res.end(),v.begin(),v.end());
    return res;
}

// 100% https://app.codility.com/demo/results/trainingNC78WH-5N2/
int oddOccurencesInArray(std::vector<int> &A) {
    std::sort(A.begin(),A.end());
    for(int i=0;i<A.size();i+=2){
        if(i+1>=A.size() || A[i]!=A[i+1]){
            return A[i];
        }
    }
}

//100% O(N) https://app.codility.com/demo/results/trainingNGURKC-WUG/
int tapeEquilibrium(std::vector<int> &A) {
    std::vector<int> sum = {A[0]};
    for(int i=1;i<A.size();i++){
        sum.emplace_back(sum[i-1]+A[i]);
    }
    int diff = abs(sum[0]-(sum[sum.size()-1]-sum[0]));
    //cout<<diff<<endl;
    for(int i=0;i<A.size()-1;i++){
        int res = abs(sum[i]-(sum[sum.size()-1]-sum[i]));
        if(res<diff)diff=res;
        //cout<<i<<": "<<diff<<endl;
    }
    return diff;
}

std::string vectorIntToString(std::vector<int>v){
    std::string res = "{";
    for(int n : v){
        res+=std::to_string(n)+", ";
    }
    res+="}";
    return res;
} 

enum EExercices{
    TSP,
    BINARY_GAP,
    FROG_JMP,
    PERM_MISSING_ELEM,
    CYCLIC_ROTATION,
    ODD_OCCURENCES,
    TAPE_EQUILIBRIUM
};

int main(int argc, char* argv[])
{
    EExercices exToTest = TSP; //Change here
    switch (exToTest){
    case TSP:{
        Path result = resolve(0,{false,false,false,false,false},0);
        std::cout<<"cost: "<<result.cost<<std::endl;
        std::cout<<"path : ";
        for(int i : result.path){
            std::cout<<i<<"  ";
        }
        std::cout<<std::endl;
        break;
    }
    case BINARY_GAP:{
        int N=156; //Change here
        std::cout<<"Max binary gap for "<<N<<" is "<<binaryGap(N)<<std::endl;
        break;
    }
    case FROG_JMP:{
        int X=10,Y=50,D=6; //Change here
        std::cout<<"It requires "<<frogJMP(X,Y,D)<<" jumps to reach "<<Y<<" from "<<X<<" by jumping "<<D<<" each time"<<std::endl;
        break;
    }
    case PERM_MISSING_ELEM:{
        std::vector<int>A={1,2,7,5,6,3}; //Change here
        std::cout<<"The vector "<<vectorIntToString(A)<<" is missing the number "<<permMissingElem(A)<<std::endl;
        break;
    }
    case CYCLIC_ROTATION:{
        std::vector<int>A={1,5,4,8,9,56,7,8,54,2,84}; //Change here;
        int K = 5; //Change here
        std::vector<int>res = cyclicRotation(A,K);
        std::cout<<"The vector "<<vectorIntToString(A)<<" after "<<K<<" rotation to the right is "<<vectorIntToString(res)<<std::endl;
        break;
    }
    case ODD_OCCURENCES:{
        std::vector<int>A = {1,5,2,1,4,3,3,5,2}; //Change here;
        std::cout<<"The number missing its pair in the vector "<<vectorIntToString(A)<<" is "<<oddOccurencesInArray(A)<<std::endl;
        break;
    }
    case TAPE_EQUILIBRIUM:{
        std::vector<int>A = {1,5,98,6,74,25,3,3,6}; //Change here
        std::cout<<"The minimum difference between the sums of two parts of the vector "<<vectorIntToString(A)<<" is "<<tapeEquilibrium(A)<<std::endl;
        break;
    }
    }
    return 0;
}

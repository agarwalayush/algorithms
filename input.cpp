#include<iostream>
#include<time.h>
#include<random>
#include<cstdlib>
//using namespace std;
int main(){
//    srand(static_cast <unsigned> (time(0)));
 std::random_device rd;
 std::mt19937 gen(rd());
 std::uniform_real_distribution<> dis(0, 1);
 int n,m=10000000;
    double d=1.0;
    long long r=RAND_MAX;
    std::cin>>n;
    std::cout<<n<<"\n";
    for(int i=0;i < 2*n; i++){
        std::cout<< dis(gen)<<" "<< dis(gen)<<" "<< dis(gen)<<"\n";
        //cout<< (d*(rand()%m))/r<<" "<< (d*(rand()%m))/r<<" "<< (d*(rand()%m))/r<<endl;
    }
}

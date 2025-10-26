#include "../random.h"
#include<bits/stdc++.h>
using namespace std;
using namespace Rand;
constexpr int N=100;

String gen;

int main(){
    cout<<"1\n";
    cout<<N<<'\n';
    for(int i=1;i<=N;i++){
        string a=gen.strselect("114","514","191","981","9191");
        string b=gen.strselect("114","514","191","981","9191");
        while(a==b){
            a=gen.strselect("114","514","191","981","9191");
            b=gen.strselect("114","514","191","981","9191");
        }
        cout<<a<<" "<<b<<'\n';
    }
    return 0;
}
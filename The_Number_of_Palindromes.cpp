#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int MN=1e5+15;
const ull P=131;
int T;
ull hsh[MN],p[MN];
string in,s;
map<ull,int> mp;

void init(){
    mp.clear();
    s.clear();
}

int main(){
    p[0]=1;
    for(int i=1;i<MN;i++){
        p[i]=p[i-1]*P;
    }
    cin>>T;
    while (T--)
    {
        cin>>in;
    }
    
    return 0;
}
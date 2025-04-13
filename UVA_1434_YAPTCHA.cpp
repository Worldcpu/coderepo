#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e6+100;
int T,cnt[MN];


vector<bool> notprime(MN+5),isprime(MN+15);

vector<int> prime;

void shai(int n){
    for(int i=2;i<=n;i++){
        if(!notprime[i]){
            isprime[i]=1;
            prime.push_back(i);
        }
        for(auto p:prime){
            if(i*p>n) break;
            notprime[i*p]=1;
            if(i%p==0) break;
        }
    }
}

int main(){
    shai(3e6+15);
    for(int i=1;i<=1e6;i++){
        cnt[i]=cnt[i-1]+isprime[3*i+7];
    }
    cin>>T;
    while (T--)
    {
        int x;
        cin>>x;
        cout<<cnt[x]<<'\n';
    }
    
    return 0;
}
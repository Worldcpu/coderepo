#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,k,q;
char s[MN];
string st;

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    m+=k;
    for(int i=0;i<m;i++){
        int f,l,r,c;
        cin>>f>>l>>r>>c;
        if(f==1){
            memset(s+l,c+'0',r-l+1);
        }else{
            cout<<(memcmp(s+l,s+l+c,r-l-c+1)?"NO":"YES")<<'\n';
        }
    }
    return 0;
}
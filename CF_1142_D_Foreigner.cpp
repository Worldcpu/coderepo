#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,f[MN][15],ans;
string st;

int nxt(int x,int c){
	return (x*(x-1)/2+c+10)%11;
}

signed main(){
    cin>>st;
    n=st.length();
    st=" "+st;
    for(int i=1;i<=n;i++){
        int ch=st[i]-'0';
        if(ch>0) f[i][ch]++;
        for(int j=ch+1;j<=10;j++){
            f[i][nxt(j,ch)]+=f[i-1][j];
        }
        for(int j=0;j<=10;j++) ans+=f[i][j];
    }
    cout<<ans;
    return 0;
}
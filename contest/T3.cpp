#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5+15;
int cntc,cnts,n;
string c,s;
vector<pir> op;

int main(){
    freopen("YC.in","r",stdin);
    freopen("YC.out","w",stdout);
    cin>>c>>s;
    for(int i=0;i<c.length();i++){
        if(c[i]=='0') cntc++;
        if(s[i]=='0') cnts++;
    }
    if(cntc!=cnts){
        cout<<"NO";
        return 0;
    }
    for(int i=0;i<c.length();i++){
        if(c[i]!=s[i]){
            int cnt1=0;
            bool flag=0;
            for(int j=i;j<c.length();j++){
                if(c[j]=='1') cnt1++;
                if(!(cnt1&1)&&c[j]==s[i]){
                    op.push_back(pir(i+1,j+1));
                    int x=i,y=j;
                    while(x<y){
                        swap(c[x],c[y]);
                        x++,y--;
                    }
                    flag=1;
                    break;
                }
            }
            if(!flag){
                cout<<"NO";
                return 0;
            }
        }
    }
    cout<<"YES\n"<<op.size()<<'\n';
    for(auto p:op) cout<<p.first<<" "<<p.second<<'\n';
    
    return 0;
}

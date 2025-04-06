#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MK=6;
int T,k,p[MK];

int main(){
    while (cin>>k)
    {
        memset(p,0,sizeof(p));
        if(k==0) continue;
        for(int i=1;i<=k;i++){
            cin>>p[i];
        }
        ll f[p[1]+1][p[2]+1][p[3]+1][p[4]+1][p[5]+1]{};
        f[0][0][0][0][0]=1;
        for(int a1=0;a1<=p[1];a1++){
            for(int a2=0;a2<=p[2];a2++){
                for(int a3=0;a3<=p[3];a3++){
                    for(int a4=0;a4<=p[4];a4++){
                        for(int a5=0;a5<=p[5];a5++){
                            if(a1<p[1]){
                                f[a1+1][a2][a3][a4][a5]+=f[a1][a2][a3][a4][a5];
                            }
                            if(a2<p[2]&&a2<a1){
                                f[a1][a2+1][a3][a4][a5]+=f[a1][a2][a3][a4][a5];
                            }
                            if(a3<p[3]&&a3<a2){
                                f[a1][a2][a3+1][a4][a5]+=f[a1][a2][a3][a4][a5];
                            }
                            if(a4<p[4]&&a4<a3){
                                f[a1][a2][a3][a4+1][a5]+=f[a1][a2][a3][a4][a5];
                            }
                            if(a5<p[5]&&a5<a4){
                                f[a1][a2][a3][a4][a5+1]+=f[a1][a2][a3][a4][a5];
                            }
                        }
                    }
                }
            }
        }
        cout<<f[p[1]][p[2]][p[3]][p[4]][p[5]]<<'\n';
    }
    
    return 0;
}
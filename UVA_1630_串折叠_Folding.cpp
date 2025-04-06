#include<bits/stdc++.h>
using namespace std;
const int MN=256;
struct previous{
    int i1,j1,i2,j2;
    int isnum=0;
}pre[MN][MN];
string s;
int f[MN][MN],num[101],n;

bool check(int l,int r,int lenn){
    for(int i=l;i<l+lenn;i++){
        for(int j=i;j<=r;j+=lenn){
            if(s[i]!=s[j]) return 0;
        }
    }
    return 1;
}

void getans(int i,int j){
    if(i==0||j==0) return;
    // cout<<i<<" "<<j<<'\n';
    if(i==j) cout<<s[i];
    previous p=pre[i][j];
    if(p.isnum){
        cout<<p.isnum<<"(";
        getans(p.i1,p.j1);
        cout<<")";
    }else{
        getans(p.i1,p.j1);
        getans(p.i2,p.j2);
    }
    // // cout<<"PRE:"<<p.i1<<" "<<p.j1<<" "<<p.i2<<" "<<p.j2<<" "<<p.isnum<<'\n';
    // getans(p.i1,p.j1);
    // getans(p.i2,p.j2);
}

int main(){
    for(int i=1;i<=100;i++){
        if(i>=1&&i<=9) num[i]=1;
        else if(i>=10&&i<=99) num[i]=2;
        else num[i]=3;
    }
    while (cin>>s)
    {
        // cout<<"DATA!\n";
        memset(f,0x3f,sizeof(f));
        memset(pre,0,sizeof(pre));
        n=s.length();
        s=' '+s;
        for(int i=1;i<=n;i++){
            f[i][i]=1;
        }
        for(int len=2;len<=n;len++){
            for(int l=1;l+len-1<=n;l++){
                int r=l+len-1;
                for(int k=l;k<r;k++){
                    if(f[l][r]>f[l][k]+f[k+1][r]){
                        f[l][r]=f[l][k]+f[k+1][r];
                        pre[l][r]={l,k,k+1,r,0};
                    }
                    int lk=k-l+1;
                    if(len%lk) continue;
                    if(check(l,r,lk)){
                        if(f[l][r]>num[len/lk]+2+f[l][k]){
                            f[l][r]=num[len/lk]+2+f[l][k];
                            pre[l][r]={l,k,0,0,len/lk};
                        }
                    }
                }
            }
        }
        // cout<<f[1][n]<<"\n";
        getans(1,n);
        cout<<'\n';
    }
    
    return 0;
}
// AAAAAAAAAABABABCCD
// N E E R C YESYESYES NEERCYESYESYES

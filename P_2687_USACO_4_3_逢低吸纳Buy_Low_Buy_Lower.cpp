#include<bits/stdc++.h>
#define ill __int128
using namespace std;
template<typename type>
inline void write(type x,bool mode=1)//0为空格，1为换行
{
    x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10; while(x);
    while(top) putchar(Stack[top--]|48);
    mode?putchar('\n'):putchar(' ');
}
const int MN=5200;
int n,a[MN],f[MN];
long double c[MN]{},ans;
int maxx=-1e9;
// map<int,bool> m;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        f[i]=c[i]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(a[j]>a[i]){
                if(f[j]+1>f[i]){
                    f[i]=f[j]+1;
                    c[i]=c[j];
                }else if(f[j]+1==f[i]){
                    c[i]+=c[j];
                }
            }
            if(a[i]==a[j]){
                c[i]=0;
            }
        }
        maxx=max(maxx,f[i]);
    }
    for(int i=1;i<=n;i++){
        if(f[i]==maxx){
            ans+=c[i];
        }
    }
    cout<<maxx<<" "<<fixed<<setprecision(0)<<ans;
    return 0;
}
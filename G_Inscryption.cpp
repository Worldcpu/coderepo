#include<iostream>
#include<algorithm>
using namespace std;
const int MN=1e6+15;
int n,T;
int a[MN];
template<typename type>
inline void read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
void solve(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    int p=1,q=1,c=0;
    bool notavail=0;
    for(int i=1;i<=n;i++){
        if(a[i]==1){
            p++;
            q++;
        }else if(a[i]==-1){
            if(q>=2){
                q--;
            }else if(c>0){
                q++;
                p++;
                c--;
            }
            else{
                notavail=1;
            }
        }else{
            if(q>1){
                c++;
                q--;
            }else{
                p++;
                q++;
            }
        }
    }
    if(notavail){
        cout<<-1<<'\n';
    }else{
        int gcd=__gcd(p,q);
        cout<<p/gcd<<" "<<q/gcd<<'\n';
    }
}
int main(){
    ios::sync_with_stdio(0);
    read(T);
    while (T--)
    {
        solve();
    }
    
    return 0;
}
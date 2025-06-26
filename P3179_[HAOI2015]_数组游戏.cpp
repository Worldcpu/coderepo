#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int sg[2][MN],rt[MN],pos[MN],tot,n,n2,T;

inline int SG(int x)
{
	return ((x=n/(n/x))>n2)?sg[1][n/x]:sg[0][x];
}

void init(){
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        rt[++tot]=r;
    }
    ++tot;
    while(--tot){
        int x=rt[tot],y=0,z=1;
        pos[y]=tot;
        for(int i=x*2,j;i<=n;i=j+x){
            j=n/(n/i)/x*x,pos[y^SG(j)]=tot;
            ((j-i)/x&1^1)&&(y^=SG(j));
        }
        while(pos[z]==tot) ++z;
        (x>n2)?sg[1][n/x]=z:sg[0][x]=z;
    }
}

int main(){
    cin>>n>>T;
    while(n2*n2<=n) ++n2;
    n2--;
    init();
    while(T--){
        int w,x=0;
        cin>>w;
        for(int i=1;i<=w;i++){
            int awa;
            cin>>awa;
            x^=SG(awa);
        }
        cout<<(x?"Yes":"No")<<'\n';
    }

    return 0;
}

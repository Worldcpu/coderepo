#include<iostream>
#define endl '\n'
using namespace std;
const int MN=2e6+16,ML=45;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int st[MN][ML];
int ask(int l,int r){
    int k=__lg(r-l+1);
    return max(st[l][k],st[r-(1<<k)+1][k]);
}
int n,q;
int main(){
    n=read();
    q=read();
    for(int i=1;i<=n;i++){
        st[i][0]=read();
    }
    for(int i=1;i<=30;i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            st[j][i]=max(st[j][i-1],st[j+(1<<i-1)][i-1]);
        }
    }
    for(int i=1;i<=q;i++){
        int l=read(),r=read();
        cout<<ask(l,r)<<endl;
    }
    return 0;
}
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
constexpr int MN=5e7+15,B=17,MV=64;
int n,f[MV],g[MV],lst[MV],slen;
ull a[MV],suma[MV],cnt[MV],ans;

namespace READ
{
	ull Read()
	{
		char ch=getchar();
		ull s=0;
		while(ch<'0'||ch>'9') ch=getchar();
		while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
		return s;
	}
	ull tp[10005];
	int l,r;
	ull g1,g2;
	void init(int &n)
	{
		int i,k;
		n=Read(),k=Read(),l=1;
		for(i=1;i<=k;i++)
			tp[i]=Read();
	}
	ull read()
	{
		if(l>r)
			l=Read(),r=Read(),g1=Read(),g2=Read();
		return tp[l++]*g1+g2;
	}
}
 

ull lowbit(ull x){
    return x&-x;
}

void initB(){
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
}

signed main(){
    READ::init(n);
    for(int bl=1;bl<=n;bl+=B){
        int br=min(bl+B-1,n),len=br-bl+1;
        slen+=1ull*len*(len+1)/2;
        for(int j=bl;j<=br;j++){
            a[j-bl+1]=READ::read();
        }
        for(int i=1;i<=len;i++){
            ull ret=0;
            for(int j=i;j<=len;j++){
                ret|=a[j];
                ans+=ret;
            }
        }
        initB();
        suma[0]=0;
        for(int i=1;i<=len;i++){
            suma[i]=(suma[i-1]|a[i]);
        }
        for(int i=1;i<=len;i++){
            ull x=(suma[i]^suma[i-1]);
            while(x){
                f[__builtin_ctzll(x)]=i+bl-1;
                x^=lowbit(x);
            }
        }
        suma[len+1]=0;
        for(int i=len;i>=1;i--){
            suma[i]=(suma[i+1]|a[i]);
        }
        for(int i=1;i<=len;i++){
            ull x=(suma[i]^suma[i+1]);
            while(x){
                g[__builtin_ctzll(x)]=i+bl-1;
                x^=lowbit(x);
            }
        }
        for(int i=0;i<64;i++){
            if(f[i]){
                cnt[i]+=1ull*(f[i]-bl)*(bl-lst[i]-1);
                lst[i]=g[i];
            }else{
                cnt[i]+=1ull*(br-bl+1)*(bl-lst[i]-1);
            }
        }
    }
    for(int i=0;i<64;i++){
        ans+=(1ull<<i)*(1ull*n*(n+1)/2-slen-cnt[i]);
    }
    cout<<ans;
    return 0;
}
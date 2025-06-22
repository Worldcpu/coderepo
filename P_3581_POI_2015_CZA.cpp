#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15,MOD=1e9+7;
int n,tjans,k,p,f[MN][2][9];
bool h[MN][10];

namespace tj{

#include<bits/stdc++.h>
#define LL long long
#define UN unsigned
using namespace std;
//--------------------//
const int N=1e6+5,Mod=1e9+7;

int n,k,p,f[N][2][8];
bool ht[N][10];
void add(int &x,int y){x+=y,x-=((x>=Mod)?Mod:0);}//优化取模
bool sit(int x,int y){return abs(x-y)<=p&&!ht[y][y-x+3];}//判断是否能坐在右面
bool ck1(int i,int j,int st,int pos)//判断是否合法
{
	if(j)
	{
		if(pos==1)
			return ((!(st&4)||sit(i+3,i+1))&&(!(st&2)||sit(i+2,i+3)));
		if(pos==2)
			return (sit(i,i+3)&&(!(st&4)||sit(i+3,i+1)));
		return (sit(i+3,i)&&(!(st&2)||sit(i+2,i+3)));
	}
	if(pos==1)
		return (!(st&4)||sit(i+1,i+3))&&(!(st&2)||sit(i+3,i+2));
	if(pos==2)
		return (sit(i+3,i)&&(!(st&4)||sit(i+1,i+3)));
	return (sit(i,i+3)&&(!(st&2)||sit(i+3,i+2)));
}
bool ck2(int i,int j,int st,int pos)//判断 i=1 时是否合法
{
	if(i>1)
		return true;
	if(j)
	{
		if(pos==1)
			return (sit(1,3)&&sit(2,1));
		if(pos==2)
			return (sit(3,1)&&(!(st&1)||sit(2,3)));
		return (sit(1,2)&&(!(st&1)||sit(2,3)));
	}
	if(pos==1)
		return (sit(3,1)&&sit(1,2));
	if(pos==2)
		return (sit(1,3)&&(!(st&1)||sit(3,2)));
	return (sit(2,1)&&(!(st&1)||sit(3,2)));
}
//--------------------//
int solve()
{
    if(p==0)//分讨
    {
        if(n==1)
            return 1;
        else
            return 0;
    }
    if(p==1)
    {
        if(n==1||(n==2&&k==0))
            return 1;
        else
            return 0;
        return 0;
    }
	if(n==1)
		return 1;
	if(n==2) return (k?0:1);
    if(p==2)
    {
        int ans=0;
        //顺时针
        bool flag=((!sit(n-1,n))|((n&1)&&!sit(1,2))|((!(n&1))&&!sit(2,1)));
        for(int i=n-1;i>2;i-=2)
            flag|=!sit(i-2,i);
        for(int i=n-2;i>2;i-=2)
            flag|=!sit(i,i-2);
        //逆时针
        ans+=!flag,flag=((!sit(n,n-1))|((n&1)&&!sit(2,1))|((!(n&1))&&!sit(1,2)));
        for(int i=n-1;i>2;i-=2)
            flag|=!sit(i,i-2);
        for(int i=n-2;i>2;i-=2)
        	flag|=!sit(i-2,i);
        ans+=!flag;
        return ans;
    }
	f[n-2][0][7]=f[n-2][1][7]=1;
	for(int i=n-2;i>=2;i--)//倒序转移
	{
		for(int j=0;j<=1;j++)
		{
			for(int st=0;st<=7;st++)
			{
				if(!f[i][j][st])
					continue;
				if((st&1)&&ck1(i-1,j,st,1)&&ck2(i-1,j,st,1))
					add(f[i-1][j^1][5],f[i][j][st]);
				if((st&2)&&ck1(i-1,j,st,2)&&ck2(i-1,j,st,2))
					add(f[i-1][j][4|((st&1)<<1)],f[i][j][st]);
				if((st&4)&&ck1(i-1,j,st,3)&&ck2(i-1,j,st,3))
					add(f[i-1][j][1|((st&1)<<1)],f[i][j][st]);
			}
		}
	}
	int ans=0;
	for(int i=0;i<=7;i++)//统计答案
		add(ans,f[1][0][i]),add(ans,f[1][1][i]);
    return ans;
}
}

bool sit(int x,int y){
    return abs(x-y)<=p&&!h[y][y-x+3];
}

bool check1(int i,int j,int st,int pos){
	if(j){
		if(pos==1) return ((!(st&4)||sit(i+3,i+1))&&(!(st&2)||sit(i+2,i+3)));
		if(pos==2) return (sit(i,i+3)&&(!(st&4)||sit(i+3,i+1)));
		return (sit(i+3,i)&&(!(st&2)||sit(i+2,i+3)));
	}
	if(pos==1) return (!(st&4)||sit(i+1,i+3))&&(!(st&2)||sit(i+3,i+2));
	if(pos==2) return (sit(i+3,i)&&(!(st&4)||sit(i+1,i+3)));
	return (sit(i,i+3)&&(!(st&2)||sit(i+3,i+2)));
}

bool check2(int i,int j,int st,int pos){
    if(i>1) return 1;
    if(j){
        if(pos==1) return (sit(1,3)&&sit(2,1));
        if(pos==2) return (sit(3,1)&&(!((st&1))||sit(2,3)));
        return (sit(1,2)&&((!(st&1))||sit(2,3)));
    }
    if(pos==1){
        return (sit(3,1)&&sit(1,2));
    }
    if(pos==2){
        return (sit(1,3)&&((!(st&1))||sit(3,2)));
    }
    return (sit(2,1)&&(!(st&1)||sit(3,2)));
}

void solvep0(){
    if(n==1) cout<<1;
    else cout<<0;
}

void solvep1(){
    if(n==1||(n==2&&k==0)) cout<<1;
    else cout<<0;
}

void solven(){
    if(n==1) cout<<1;
    if(n==2) cout<<(k?0:1);
}

void solvep2(){
    int ans=0;
    bool flag=((!sit(n-1,n)|((n&1)&&!sit(1,2))|((!(n&1))&&!sit(2,1))));
    for(int i=n-1;i>2;i-=2){
        flag|=!sit(i-2,i);
    }
    for(int i=n-2;i>2;i-=2){
        flag|=!sit(i,i-2);
    }
    ans+=!flag;
    flag=((!sit(n,n-1)|((n&1)&&!sit(2,1))|((!(n&1))&&!sit(1,2))));
    for(int i=n-1;i>2;i-=2){
        flag|=!sit(i,i-2);
    }
    for(int i=n-2;i>2;i-=2){
        flag|=!sit(i-2,i);
    }
    ans+=!flag;
   cout<<(tjans!=ans?tjans:ans);
}

void solvep3(){
    f[n-2][0][7]=f[n-2][1][7]=1;
    for(int i=n-2;i>=2;i--){
        for(int j=0;j<2;j++){
            for(int k=0;k<=7;k++){
                if(!f[i][j][k]) continue;
                if((k&1)&&check1(i-1,j,k,1)&&check2(i-1,j,k,1)){
                    f[i-1][j^1][5]=(f[i-1][j^1][5]+f[i][j][k])%MOD;
                }
                if((k&2)&&check1(i-1,j,k,2)&&check2(i-1,j,k,2)){
                    f[i-1][j][4|((k&1)<<1)]=(f[i-1][j][4|((k&1)<<1)]+f[i][j][k])%MOD;
                }
                if((k&4)&&check1(i-1,j,k,3)&&check2(i-1,j,k,3)){
                    f[i-1][j][1|((k&1)<<1)]=(f[i-1][j][1|((k&1)<<1)]+f[i][j][k])%MOD;
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<=7;i++){
        ans=(ans+f[1][0][i])%MOD;
        ans=(ans+f[1][1][i])%MOD;
    }
    cout<<ans;
}

signed main(){
    cin>>n>>k>>p;
    for(int i=1;i<=k;i++){
        int x,y;
        cin>>x>>y;
        if(abs(x-y)<=p){
            h[x][x-y+3]=1;
            tj::ht[x][x-y+3]=1;
        }
    }
    tjans=tj::solve();
    if(p==0) solvep0();
    else if(p==1) solvep1();
    else if(n<3) solven();
    else if(p==2) solvep2();
    else if(p==3) solvep3();
    return 0;
}

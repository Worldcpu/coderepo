//#include<iostream>
//#include<cmath>
//#define ll long long
//#define ML 30
//#define MN 100010
//using namespace std;
//int st[MN][ML],stmin[MN][ML],n,m,a[MN];
//int ask(int l,int r){
//    int k=log2(r-l+1);
//    int x=max(st[l][k],st[r-(1<<k)+1][k]),y=min(stmin[l][k],stmin[r-(1<<k)+1][k]);
//    return x-y;
//}
//int main(){
//    #ifndef ONLINE_JUDGE
//    freopen("ans.in","r",stdin);
//    #endif
//    // for(int i=1;i<ML;i++){
//    //     cout<<p[i]<<" ";
//    // }
//    // cout<<endl;
//    cin>>n>>m;
//    for(int i=1;i<=n;i++){
//        cin>>a[i];
//        st[i][0]=a[i];
//        stmin[i][0]=a[i];
//    }
//    for(int i=1;i<=20;i++){
//        for(int j=1;j+(1<<i)<=n+1;j++){
//                st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
//                stmin[j][i]=min(stmin[j][i-1],stmin[j+(1<<(i-1))][i-1]);
//        }
//    }
//    for(int i=1;i<=m;i++){
//        int x,y;
//        cin>>x>>y;
//        cout<<ask(x,y)<<"\n";
//    }
//    return 0;
//}
#include<iostream>
#define MN 50010
#define ML 30
using namespace std;
int stmax[MN][ML],stmin[MN][ML],lg[MN],pw[ML],n,q;
void initlg(){
	lg[1]=0;
	for(int i=2;i<MN;i++){
		lg[i]=lg[i-1]+(i==1<<(lg[i-1]+1));
	}
}
void initpw(){
	pw[0]=1;
	for(int i=1;i<ML;i++){
		pw[i]=pw[i-1]*2;
	}
}
int ask(int l,int r){
	int k=lg[r-l];
	int x=max(stmax[l][k],stmax[r-(1<<k)+1][k]),y=min(stmin[l][k],stmin[r-(1<<k)+1][k]);
	return x-y;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("ans.in","r",stdin);
	#endif
	cin>>n>>q;
	initpw();
	initlg();
	for(int i=1;i<=n;i++){
		cin>>stmax[i][0];
		stmin[i][0]=stmax[i][0];
	}
	for(int i=1;i<=20;i++){
		for(int j=1;j+pw[i]<=n+1;j++){
			stmax[j][i]=max(stmax[j][i-1],stmax[j+(1<<(i-1))][i-1]);
			stmin[j][i]=min(stmin[j][i-1],stmin[j+(1<<(i-1))][i-1]);
		}
	}
	for(int i=1;i<=q;i++){
		int l,r;
		cin>>l>>r;
		cout<<ask(l,r)<<"\n"; 
	}
	
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,fa[100015],faa[100015];
random_device rd;

int zhao(int xx){
	if(fa[xx]==xx) return xx;
	else return zhao(fa[xx]);
}

int getrd(int l,int r){
    return rand()%(r-l+1)+l;
}

int main(){
    freopen("dp.in","w",stdout);
    srand(time(0)*rd());
	int n=getrd(10,20);
    cout<<n<<'\n';
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	while(cnt<n-1){
		int x=rand()%n+1,y=rand()%n+1;
		int x1=zhao(x),y1=zhao(y);
		if(x1!=y1){
			fa[x1]=y1,cnt++;
			printf("%d %d\n",x,y);
		}
	}
	return 0;
}

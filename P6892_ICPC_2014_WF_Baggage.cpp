#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
int n;
vector<pir> op;

void dfs(int l,int r){
	if((r-l+1)/2==4)cout<<l+5<<" to "<<l-2<<"\n"<<l+2<<" to "<<l+5<<"\n"<<l-1<<" to "<<l+2<<"\n"<<l+6<<" to "<<l-1<<"\n";
	else if((r-l+1)/2==5)cout<<l+7<<" to "<<l-2<<"\n"<<l+2<<" to "<<l+7<<"\n"<<l+5<<" to "<<l+2<<"\n"<<l-1<<" to "<<l+5<<"\n"<<l+8<<" to "<<l-1<<"\n";
	else if((r-l+1)/2==6)cout<<l+9<<" to "<<l-2<<"\n"<<l+6<<" to "<<l+9<<"\n"<<l+1<<" to "<<l+6<<"\n"<<l+5<<" to "<<l+1<<"\n"<<l-1<<" to "<<l+5<<"\n"<<l+10<<" to "<<l-1<<"\n";
	else if((r-l+1)/2==7)cout<<l+7<<" to "<<l-2<<"\n"<<l+4<<" to "<<l+7<<"\n"<<l+11<<" to "<<l+4<<"\n"<<l+2<<" to "<<l+11<<"\n"<<l+8<<" to "<<l+2<<"\n"<<l-1<<" to "<<l+8<<"\n"<<l+12<<" to "<<l-1<<"\n";
	else cout<<r-2<<" to "<<l-2<<"\n"<<l+2<<" to "<<r-2<<"\n",dfs(l+4,r-4),cout<<l-1<<" to "<<r-5<<"\n"<<r-1<<" to "<<l-1<<"\n";
	return;
}


int main(){
    while(cin>>n){
        if(n==3){
            cout<<"2 to -1\n5 to 2\n3 to -3\n\n";
            continue;
        }
        dfs(1,2*n);
        for(auto p:op){
            cout<<p.first<<" to "<<p.second<<'\n';
        }
        cout<<'\n';
    }
    return 0;
}

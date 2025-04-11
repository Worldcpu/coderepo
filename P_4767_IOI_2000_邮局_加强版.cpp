#include<bits/stdc++.h>
#define getr(l,r) ((mt()%(r-l+1)+l))
using namespace std;
random_device rd;
mt19937 mt;
int n,a[250];

int val(int i,int j){
    int mid=(i+j)>>1;
    int ans=0;
    for(int p=i;p<=j;p++){
        ans+=abs(a[mid]-a[p]);
    }
    return ans;
}

bool check(){
    sort(a+1,a+1+n);
    // for(int i=1;i<=n;i++){
    //     cout<<a[i]<<" ";
    // }
    for(int a=1;a<=n;a++){
        for(int b=a+1;b<=n;b++){
            for(int c=b+1;c<=n;c++){
                for(int d=c+1;d<=n;d++){
                    if(val(a,d)+val(b,c)<val(a,c)+val(b,d)) return 0;
                }
            }
        }
    }
    return 1;
}

map<int,bool>vis;

int main(){
    int cnt=0;
    cin>>n;
    mt.seed(rd());
    while(cnt<=100){
        vis.clear();
        for(int i=1;i<=n;i++){
            bool flag=0;
            while(!flag){
                a[i]=getr(1,10000);
                if(!vis[a[i]]) flag=1;
            }
        }
        if(check()){
        }else{ cout<<"WA!";break;}
        cnt++;
    }
    return 0;
}
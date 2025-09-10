#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int pre[MN],siz[MN];
vector<int> adj[MN];

int root(int x){
    if(pre[x]==x) return pre[x];
    return pre[x]=root(pre[x]);
}

namespace Tree{

}


int main(){

    return 0;
}
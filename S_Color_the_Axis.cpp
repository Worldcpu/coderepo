#include<iostream>
#include<set>
using namespace std;
int sum;
struct node
{
    int l,r;
    mutable int val;
    node(int L,int R=-1,int Val=0){
        l=L;
        r=R;
        val=Val;
    }
    bool operator<(const node&x)const{
        return l<x.l;
    }
};
set<node> s;
auto split(int pos){
    auto it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos){
        return it;
    }
    it--;
    int l=it->l,r=it->r,val=it->val;
    s.erase(it);
    s.insert(node(l,pos-1,val));
    return s.insert(node(pos,r,val)).first;
}
void assign(int l,int r,int val){
    auto itr=split(r+1);
    auto itl=split(l);
    for(auto it=itl;it!=itr;it++){
        sum-=it->val*(it->r-it->l+1);
    }
    s.erase(itl,itr);
    s.insert(node(l,r,val));
}
int main(){
    int n,m;
    cin>>n>>m;
    // cout<<"AWA"<<endl;
    for(int i=1;i<=n;i++){
        s.insert(node(i,i,1));
        sum++;
    }
    while (m--){
        int l,r;
        cin>>l>>r;
        assign(l,r,0);
        cout<<sum<<endl;
    }
    
    return 0;
}
#include<iostream>
#include<set>
#include<algorithm>
#include<vector>
#define ll long long
using namespace std;
const int MOD=1000000007,MN=1e5+15;
ll n,m,seed,vmax;
ll a[MN];
ll rnd(){
    ll ret=seed;
    seed=(seed*7+13)%MOD;
    return ret;
}

struct kdltree
{
    int l,r;
    mutable ll val;//set里面的元素一般不可修改，用mutable修饰就珂以修改
    kdltree(int L,int R=-1,ll V=0){
        //构造函数，左端点是必须有，若后面不添加R和V（就是val）默认就是单独的一个端点[pos,pos]
        l=L,r=R,val=V;
    }
    bool operator<(const kdltree&a)const{
        return l<a.l;
    }
};
set<kdltree> odt;

//分割区间，把区间分成[l,pos-1],[pos,r]
auto split(int pos){
    auto it=odt.lower_bound(kdltree(pos));//找第一个左端点不小于pos的的区间
    if(it!=odt.end()&&it->l==pos){
        return it;//pos是左端点是无需分裂
    }
    it--;//pos一定在前一个区间；
    int l=it->l,r=it->r;
    ll val=it->val;
    odt.erase(it);//删除原来的区间
    odt.insert(kdltree(l,pos-1,val));
    return odt.insert(kdltree(pos,r,val)).first;//这里返回的是指向[pos,r]这个区间的迭代器
}

//合并区间并赋值x
void merge(int l,int r,ll val){
    //注意顺序！先右端点后左端点不然可能会RE！
    auto itr=split(r+1);
    auto itl=split(l);
    odt.erase(itl,itr);//删除[l,r]区间内所有元素
    //其实这里是[l,r+1)(由于set删除特性经典左闭右开)
    //但是r+1取不到也就只能取到r了
    odt.insert(kdltree(l,r,val));//插入大区间
}
//所有的区间操作可以套一个模板
//先split右，在split左把区间[l,r]搞出来
//让后直接暴力！

//区间加
void add(int l,int r,ll val){
    auto itr=split(r+1);
    auto itl=split(l);
    for(auto it=itl;it!=itr;it++){
        it->val+=val;//这就是为啥用mutable的原因
    }
}

typedef pair<ll,int> kdl;//前人种树后人看动漫
//区间第k小
ll topk(int l,int r,int k){
    vector<kdl> a;
    auto itr=split(r+1);
    auto itl=split(l);
    for(auto it=itl;it!=itr;it++){
        a.push_back(kdl(it->val,it->r-it->l+1));
        //sort会先比较val，如果val相同则比较区间长度
        //升序保证第k小，第k大倒序即可
    }   
    sort(a.begin(),a.end());
    for(auto it=a.begin();it!=a.end();it++){
        k-=it->second;
        if(k<=0){
            return it->first;//找到了
        }
    }
    return -1;//不好没找到
}

ll fastpow(ll x,ll y,ll mod){
    ll res=1;
    x%=mod;
    while (y>0)
    {
        if(y&1){
            res=res*x%mod;
        }
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

ll sum(int l,int r,int x,int y){
    ll ans=0;
    auto itr=split(r+1);
    auto itl=split(l);
    for(auto it=itl;it!=itr;it++){
        ans=(ans+fastpow(it->val,x,y)*(it->r-it->l+1))%y;
    }
    return ans;
}
int main(){
    cin>>n>>m>>seed>>vmax;
    for(int i=1;i<=n;i++){
        a[i]=rnd()%vmax+1;
        odt.insert(kdltree(i,i,a[i]));
    }
    for(int i=1;i<=m;i++){
        int op=rnd()%4+1,l=rnd()%n+1,r=rnd()%n+1,x,y;
        if(l>r) swap(l,r);
        if(op==3){
            x=rnd()%(r-l+1)+1;
        }else x=rnd()%vmax+1;
        if(op==4) y=rnd()%vmax+1;
        if(op==1){
            add(l,r,x);
        }else if(op==2){
            merge(l,r,x);
        }else if(op==3){
            cout<<topk(l,r,x)<<endl;
        }else cout<<sum(l,r,x,y)<<endl;
    }
    return 0;
}
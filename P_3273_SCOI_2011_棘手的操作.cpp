
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 310000
#define val(p) t[p].val
#define ls(p) t[p].ls
#define rs(p) t[p].rs
#define dis(p) t[p].dist
#define siz(p) tp[p].siz
#define tag(p) tp[p].tag

int n,Q,x,y;
string op;
int a[N],rt[N];
bool del[N];//记录已经被删除的数 

/*左偏树*/
struct LLT{
	int val,ls,rs,dist;
}t[N];
struct tops{
	int siz,tag;
	/*我们在堆顶维护一个标记代表整个堆的区间加操作，siz维护堆的大小。每次合并
	时，需要同时合并标记，则对siz较小的一方暴力下传标记更新堆内的值，然后合并后
	堆顶的标记直接继承siz较大的一方*/
}tp[N]; 
multiset<int> top;
/*这个multiset维护所有堆顶的值，用于查询全局最大值。我们维护大根堆，所以堆顶的
维护值+堆顶的标记值就是实际最大值*/
int pls;//记录全局加操作的tag 

//合并操作
int merge(int x,int y){
	if(!x||!y) return x|y;//一个堆为空则返回另一个堆
	if(val(x)<val(y)) swap(x,y);//选择值较大的作为根 
	rs(x)=merge(rs(x),y);//合并右儿子和另一个堆
	if(dis(rs(x))>dis(ls(x))) swap(rs(x),ls(x));//维护左偏性质，不满足则交换儿子
	dis(x)=dis(rs(x))+1;//更新dis
	return x;//返回合并结果 
} 

//路径压缩寻找堆的
int find(int x){
	if(rt[x]==x) return x;
	return rt[x]=find(rt[x]);
}

//暴力下传
void push_down(int x,int k){
	if(!x) return;
	val(x)+=k;
	push_down(ls(x),k);
	push_down(rs(x),k);
}

signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	//freopen("P3273_2.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		val(i)=a[i];
		rt[i]=i;
		siz(i)=1;
		top.insert(val(i));
	}
	cin>>Q;
	while(Q--){
		cin>>op;
		if(op=="U"){
			cin>>x>>y;
			x=find(x);
			y=find(y);
			if(x!=y){
				if(siz(x)>siz(y)) swap(x,y);
				push_down(x,tag(x)-tag(y));
				/*暴力下传siz较小的堆的标记，同时为了消去合并后较大堆的
				标记的影响，下传的值变为两个堆标记的差*/ 
				rt[x]=rt[y]=merge(x,y);//合并 
				//判断合并到了哪个点上，更新堆顶
				if(rt[x]==x){
					top.erase(top.find(val(y)+tag(y)));//删掉被吞并的堆顶
					tag(x)=tag(y);//我们最后保留了tagy，赋值到堆顶上
					siz(x)+=siz(y);//计算合并后的大小
					tag(y)=siz(y)=0;//清空被并入的堆 
				} else {
					top.erase(top.find(val(x)+tag(y)));//删掉被吞并的堆顶
					//我们最后保留了tagy，此时堆顶就在y，不用重新赋值 
					siz(x)+=siz(y);//计算合并后的大小
					tag(x)=siz(x)=0;//清空被并入的堆
				}
			}
		}else if(op=="A1"){
			cin>>x>>y;
			/*单点赋值：删除要赋值的节点，加入赋值后的新点。由于我们只维护
			每个堆的堆顶的标记，所以需要判断x是不是堆顶采用不同的操作方式*/
			if(x==find(x)){
				//x是堆顶
				int nx=merge(ls(x),rs(x));//合并左右儿子
				top.erase(top.find(val(x)+tag(x)));//x已被删除
				//继续更新x的值
				val(x)+=y;
				ls(x)=rs(x)=0;
				dis(x)=1;
				rt[x]=rt[nx]=merge(x,nx);//重新把x合并到堆中
				top.insert(val(rt[x])+tag(x));//重新加入堆顶大小 
				if(rt[x]==nx){//如果合并后堆顶实际为nx，需要更新nx的信息 
					tag(nx)=tag(x);
					siz(nx)=siz(x);
					tag(x)=siz(x)=0; 
				} 
			} else {
				//x不是堆顶
				if(x==ls(rt[x])) ls(rt[x])=merge(ls(x),rs(x));
				else rs(rt[x])=merge(ls(x),rs(x));
				//继续更新x的值
				val(x)+=y;
				ls(x)=rs(x)=0;
				dis(x)=1;
				int nx=find(x);//找到x原本对应的堆的堆顶 
				rt[x]=rt[nx]=merge(x,nx);//重新把x合并到堆中 
				if(rt[x]==x){//如果合并后堆顶实际为x，需要更新x的信息
					top.erase(top.find(val(nx)+tag(nx)));
					top.insert(tag(nx)+val(x));
					tag(x)=tag(nx);
					siz(x)=siz(nx);
					tag(nx)=siz(nx)=0; 
				} 
			}
		}else if(op=="A2"){
			cin>>x>>y;
			x=find(x);//找到x所在连通块的堆顶 
			top.erase(top.find(val(x)+tag(x)));//删掉将被更改的堆顶
			tag(x)+=y;//更改堆顶的tag
			top.insert(tag(x)+val(x));//更改后重新加入multiset 
		}else if(op=="A3"){
			cin>>x;
			pls+=x;//全局加，直接放到全局tag上
		}else if(op=="F1"){
			cin>>x;
			//单点查询：自己的val+根的tag+全局tag 
			cout<<(val(x)+tag(find(x))+pls)<<'\n';
		}else if(op=="F2"){
			cin>>x;
			x=find(x);
			//连通块内最大值：维护了大根堆，直接找到根累加val,tag和全局tag 
			cout<<(val(x)+tag(x)+pls)<<'\n';
		}else if(op=="F3"){
			//全局最大值：从维护所有根最大值的set里挑最大的一个加上全局tag 
			cout<<(*top.rbegin()+pls)<<'\n'; 
		}
	}
	return 0;
}

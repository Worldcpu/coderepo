#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,m,X[MN],Y[MN];
int w1[MN],w2[MN],w[MN],w1tot,w2tot,ans,sumw[MN];

int solve(int x){
	int now=m-x,res=0;
	if(now==0) return 0;
	res+=2*(now/w[1]);
	w[1]<=now?now%=w[1]:0;
	auto it=lower_bound(sumw+1,sumw+1+w2tot,now)-sumw;
	if(it<=w2tot){
		if(sumw[it]==now){
			res+=it;
		}else{
			res+=it-1;
		}
	}
	return res;
}

signed main(){
	// freopen("candy.in","r",stdin);
	// freopen("candy.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>X[i]>>Y[i];
	}
	for(int i=1;i<=n;i++){
		if(X[i]>=Y[i]){
			w2[++w2tot]=X[i];
		}else{
			w1[++w1tot]=X[i];
		}
		w[i]=X[i]+Y[i];
	}
	sort(w1+1,w1+1+w1tot);
	sort(w2+1,w2+1+w2tot);
	sort(w+1,w+1+n);
	for(int i=1;i<=w2tot;i++){
		sumw[i]=sumw[i-1]+w2[i];
	}
	ans=max(ans,solve(0));
	for(int i=1,sum=0;i<=w1tot;i++){
		sum+=w1[i];
		if(sum>m) break;
		ans=max(ans,i+solve(sum));
	}
	cout<<ans<<'\n';
	return 0;
}

// 退役快乐！wjyppm！luogu：578829 
// 不过没能切 T2，暴力打错了还是很伤心的，也不知道改了能拿多少分。
// 反正这个分数应该进不了省队线，就算切了 T2 应该也不行。
// 希望文化课对我好一点。
// 再见 OI！不过我可能回去打 ACM 的，不过那也是 1 年之后的事情了。
// 预祝同学们取得好成绩，我就回去摆烂啦byebye。 
// 大学见！ 
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) ((x)&(-x))  // 计算 lowbit
using namespace std;
const int MN=1e7+15;

int n,t[MN],siz[MN],a[MN],b[MN],m,cnt,tot,ls[MN],rs[MN];
int s[MN],top,rt,qtot;  // s 是单调栈，top 是栈顶指针，rt 是笛卡尔树的根节点，qtot 是查询总数
int qr[MN],cf[MN],v[MN];  // qr 是查询的右端点，cf 是差分系数，v 是阈值
vector<int> q[MN];  // q[i] 存储右端点为 i 的所有查询

// 树状数组更新操作
void update(int x,int k){
    while(x<=n){
        t[x]+=k;
        x+=lowbit(x);
    }
}

// 树状数组查询操作
int query(int x){
    int ret=0;
    while (x)
    {
        ret+=t[x];
        x-=lowbit(x);
    }
    return ret;
}

// 笛卡尔树的 DFS 遍历，用于启发式分治
void dfs(int u,int fl,int fr){
    // u: 当前节点，fl: 当前区间的左端点，fr: 当前区间的右端点
    if(!u) return;  // 如果当前节点为空，直接返回
    siz[u]=1;  // 初始化当前子树的大小
    dfs(ls[u],fl,u-1);  // 递归处理左子树
    dfs(rs[u],u+1,fr);  // 递归处理右子树
    siz[u]+=siz[ls[u]]+siz[rs[u]];  // 更新当前子树的大小

    // 启发式分治：选择较小的子树进行枚举
    if(siz[ls[u]]<siz[rs[u]]){
        // 如果左子树较小，枚举左子树的每个元素 i
        for(int i=fl;i<=u;i++){
            qtot++;  // 查询总数加 1
            qr[qtot]=fr;  // 查询右端点为 fr
            cf[qtot]=1;  // 差分系数为 1
            v[qtot]=b[a[u]]/b[a[i]];  // 计算阈值
            qtot++;  // 查询总数加 1
            qr[qtot]=u-1;  // 查询右端点为 u-1
            cf[qtot]=-1;  // 差分系数为 -1
            v[qtot]=b[a[u]]/b[a[i]];  // 计算阈值
        }
    }else{
        // 如果右子树较小，枚举右子树的每个元素 i
        for(int i=u;i<=fr;i++){
            qtot++;  // 查询总数加 1
            qr[qtot]=u;  // 查询右端点为 u
            cf[qtot]=1;  // 差分系数为 1
            v[qtot]=b[a[u]]/b[a[i]];  // 计算阈值
            qtot++;  // 查询总数加 1
            qr[qtot]=fl-1;  // 查询右端点为 fl-1
            cf[qtot]=-1;  // 差分系数为 -1
            v[qtot]=b[a[u]]/b[a[i]];  // 计算阈值
        }
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];  // 读取数组 a
        b[++tot]=a[i];  // 将 a[i] 存入 b 数组，用于离散化
    }    
    sort(b+1,b+1+tot);  // 对 b 数组排序
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+tot,a[i])-b;  // 离散化 a 数组
    }

    // 构建笛卡尔树
    for(int i=1;i<=n;i++){
        while(top&&a[s[top]]<a[i]){
            ls[i]=s[top--];  // 弹出栈顶元素，并将其作为当前节点的左子树
        }
        rs[s[top]]=i;  // 将当前节点作为栈顶元素的右子树
        if(!top) rt=i;  // 如果栈为空，当前节点为根节点
        s[++top]=i;  // 将当前节点压入栈中
    }

    // 启发式分治，生成查询条件
    dfs(rt,1,n);

    // 处理查询条件
    for(int i=1;i<=qtot;i++){
        q[qr[i]].push_back(i);  // 将查询按右端点分组
        if(v[i]>=b[tot])v[i]=n;  // 如果阈值大于等于最大值，设为 n
        else v[i]=upper_bound(b+1,b+1+tot,v[i])-b-1;  // 离散化阈值
    }

    // 扫描线处理查询
    int ans=0;
    for(int i=1;i<=n;i++){
        update(a[i],1);  // 将 a[i] 插入树状数组
        for(auto j:q[i]){
            ans+=cf[j]*query(v[j]);  // 处理所有右端点为 i 的查询
        }
    }
    cout<<ans;  // 输出结果
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

// 定义常量与全局变量
constexpr int MN=16; // 最大列数（题目中M≤10，此处设为16足够）
constexpr int NINF=-1061109567; // 极大负数，用于初始化DP数组
int T,n,m,k; // 测试用例数，硅片的行数，列数，坏块数量
int f[2][1<<MN]; // DP数组，滚动数组存储前两行状态，2表示滚动，1<<MN是三进制状态数上限
int pw[MN]; // 3的幂次数组，用于三进制位运算
bool isbad[MN][MN]; // 标记硅片中坏块的位置

// 获取三进制数的第pos位数值（0/1/2）
int getn(int x,int pos){
    return x%pw[pos]/pw[pos-1];
}

// 判断当前位置是否可以放置芯片
bool isok(int x,int lst,int pos){
    // 当前位置非坏块，且上一行对应位置为0
    if(!isbad[x][pos]&&!getn(lst,m-pos+1)) return 1;
    return 0;
}

// 深度优先搜索生成当前行的合法状态并更新DP值
void dfs(int x,int lst,int now,int pos,int cnt){
    if(!pos){ // 所有列处理完毕
        // 更新当前行now状态的最大芯片数：前一行lst的值 + 当前cnt
        f[x%2][now] = max(f[x%2][now], f[(x-1)%2][lst] + cnt);
        return;
    }
    // 处理上一行当前列非0的情况（受约束）
    if(getn(lst,pos)){
        // 当前列损坏则无法放置
        if(isbad[x][m-pos+1]) return;
        // 根据上一列的值决定当前列只能为1或0
        if(getn(lst,pos)==2) dfs(x,lst,now*3+1,pos-1,cnt); // 上一列是2 → 当前列必须为1
        else dfs(x,lst,now*3,pos-1,cnt); // 上一列是1 → 当前列必须为0
    }else{
        // 不放置任何芯片，直接跳过
        dfs(x,lst,now*3,pos-1,cnt);
        // 尝试放置3×2竖直芯片（需要连续两列）
        if(pos>=2 && 
           isok(x,lst,m-pos+1) && 
           isok(x,lst,m-pos+2)){
            dfs(x,lst,(now*3+2)*3+2,pos-2,cnt+1);
        }
        // 尝试放置2×3水平芯片（需要连续三列）
        if(pos>=3 && 
           isok(x,lst,m-pos+1) && 
           isok(x,lst,m-pos+2) && 
           isok(x,lst,m-pos+3)){
            dfs(x,lst,((now*3+1)*3+1)*3+1,pos-3,cnt+1);
        }
    }
}

// 处理单个测试用例
void solve(){
    memset(isbad,0,sizeof(isbad)); // 清空坏块标记
    memset(f,-0x3f3f3f3f,sizeof(f)); // 初始化DP数组为极小值
    cin>>n>>m>>k;
    for(int i=1;i<=k;i++){ // 读取坏块坐标
        int x,y;
        cin>>x>>y;
        isbad[x][y]=1;
    }
    f[0][0]=0; // 初始状态：0行0状态对应0芯片
    for(int i=0;i<n;i++){ // 处理每一行（从0到n-1对应第1到第n行）
        for(int j=0;j<pw[m];j++){ // 清空下一行的DP值
            f[(i+1)%2][j]=NINF;
        }
        for(int j=0;j<pw[m];j++){ // 遍历上一行所有可能状态
            if(f[i%2][j]<0) continue; // 跳过无效状态
            dfs(i+1,j,0,m,0); // 从当前行初始状态开始递归生成
        }
    }
    cout<<f[n%2][0]<<'\n'; // 输出最终结果：最后一行状态0的最大值
}

int main(){
    pw[0]=1; // 初始化3的0次幂
    for(int i=1;i<MN;i++){ // 预计算3的幂次数组
        pw[i]=pw[i-1]*3;
    }
    cin>>T;
    while (T--){
        solve(); // 处理每组数据
    }
    return 0;
}

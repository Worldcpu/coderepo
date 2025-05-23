#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

struct RandomTreeGenerator {
    int n; // 节点数量
    std::vector<int> fa; // 父节点数组

    // 构造函数，初始化节点数量
    RandomTreeGenerator(int nodes) : n(nodes), fa(n + 1, -1) {
        srand(time(0)); // 设置随机种子，保证多次调用结果不同
    }

    // 随机生成有根树
    void generate() {
        fa.assign(n + 1, -1); // 清空父节点数组
        fa[1] = 0; // 树根为1，父节点设为0（表示无父节点）

        for (int i = 2; i <= n; ++i) {
            int parent = rand() % (i - 1) + 1; // 随机选择一个父节点（范围为1到i-1）
            fa[i] = parent;
        }
    }

    // 打印父节点数组
    void printFa() const {
        for (int i = 2; i <= n; ++i) {
            std::cout << fa[i] << " ";
        }
        std::cout << std::endl;
    }
};
using namespace std;

int main() {
    freopen("dp.out","w",stdout);
    int n = 10000,n0=10000,m=10000; // 假设有10个节点
    RandomTreeGenerator t(n);
    cout<<n<<" "<<n0<<" "<<m<<'\n';
    t.generate();
    t.printFa();
    for(int i=1;i<=n0;i++){
        cout<<rand()%n+1<<" ";
    }
    cout<<'\n';
    for(int i=1;i<=m;i++){
        int l=rand()%n0+1,r=rand()%n0+1,x=rand()%n+1;
        if(l>r) swap(l,r);
        cout<<l<<" "<<r<<" "<<x<<'\n';
    }

    return 0;
}

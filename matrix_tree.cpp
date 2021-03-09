
LL K[106][106];

LL gauss(int n){//求矩阵K的n-1阶顺序主子式
    LL res=1;
    for(int i=1;i<=n-1;i++){//枚举主对角线上第i个元素
        for(int j=i+1;j<=n-1;j++){//枚举剩下的行
            while(K[j][i]){//辗转相除
                int t=K[i][i]/K[j][i];
                for(int k=i;k<=n-1;k++)//转为倒三角
                    K[i][k]=(K[i][k]-t*K[j][k]%mod+mod)%mod;
                swap(K[i],K[j]);//交换i、j两行
                res=-res;//取负(交换两行，值取反)
            }
        }
        res=(res*K[i][i])%mod;
    }
    return (res+mod)%mod;
}//跑完后K数组改变了

//如果存在一条边x--y
//K[x][y]--;K[y][x]--;K[x][x]++;K[y][y]++;
//矩阵K的任意一个n-1阶方阵的值就是生成树的个数。
//重边要算多次.

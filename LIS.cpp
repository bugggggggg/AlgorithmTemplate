
二分：
//sta中的不是lis。
int sta[500066];
int solve(VI vec)
{
	int top=0;
	sta[0]=-1e9;
	for(auto x:vec)
	{
		if(x>=sta[top])sta[++top]=x;
		else
		{
			int p=upper_bound(sta,sta+top+1,x)-sta;
			sta[p]=x;//找到第一个大的替换掉
		}
	}
	return top;
}//非严格lis的长度。


树状数组：
//本质是优化n^2的dp；
//权值树状数组维护前缀答案的最大值，i位置维护值小于等于i的最长长度。
//新来一个a[i],
//dp[i]=query(a[i])+1,update(a[i],dp[i]);



//把一个长度为n的数组变成非严格递增，最小修改次数=n-最长非严格LIS长度；
//把一个长度为n的数组变成严格递增，最小修改次数为：
//b[i]=a[i]-i,最小修改次数=n-数组b的最长非严格LIS长度

//n-数组a的最长严格LIS长度是不对的，因为最长严格LIS的相邻数中间不一定能插入新值
//比如得到严格LIS为3，4，但3,4中还有位置，就无法满足。
#include <bits/stdc++.h>
using namespace std;

int n;
int perm[5006];

int main()
{
	random_device seed_gen;
	mt19937 engine(seed_gen());

	n=10;
	for(int i=1;i<=n;i++)perm[i]=i;
	shuffle(perm+1,perm+n+1,engine);
		
	return 0;
}

/*
	整体都进行随机打乱才能符合随机的要求
*/
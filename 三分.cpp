/*整数三分模板*/
int cal(int x){
    int res;
    return res;
}
 
int solve(int l,int r){
    while(r>l){
        int m1=(2*l+r)/3;
        int m2=(2*r+l+2)/3;
        if(cal(m1)>cal(m2))
            r-m2-1;
        else
            l=m1+1;
    }
    return l;
}
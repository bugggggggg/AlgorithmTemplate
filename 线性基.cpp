int LB[36];
void Insert(ll x)
{
    for(ll i=29;i>=0;i--)
    {
        if(((x>>i)&1))
        {
            if(!LB[i])
            {
                LB[i]=x;
                return;
            }
            else x^=LB[i];
        }
    }
}

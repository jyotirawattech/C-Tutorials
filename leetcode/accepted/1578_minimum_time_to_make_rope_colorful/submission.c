int minCost(char * s, int* cost, int costSize)
{
    int sum = 0;
    int i = 0;
    
   
    for(i=0; i<costSize-1; i++)
    {
        if(s[i]==s[i+1])
        {
            if(cost[i]<cost[i+1])
            {   sum += cost[i];
                cost[i] = cost[i+1];
            }
            else
            {
                sum += cost[i+1];
                
                cost[i+1] = cost[i];
            }
        }
    }
    //printf("\n%s",s);
    return sum;
}
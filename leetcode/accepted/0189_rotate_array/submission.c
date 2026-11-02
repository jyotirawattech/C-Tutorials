void rotate(int* nums, int numsSize, int k)
{
    int i =0;
    int temp = 0;
    if ((k == 0)||(numsSize == 0))
    {
        return;
    }
    k = k%numsSize;
    
    while(k>0)
    {
        
        temp = nums[0];
        nums[0] = nums[numsSize-1];
        for(i=numsSize-1; i>1; i--)
        {
            
            nums[i] = nums[i-1];
            
            
        }
        
        nums[1]=temp;
        
        k --;                   
        
    }
    
    
}

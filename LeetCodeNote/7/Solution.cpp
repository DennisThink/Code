class Solution {
public:
    int reverse(int x) {
        long long result = 0;
        long long xValue= x;
        
        if(x < 0)
        {
            xValue = -xValue;
        }
        else
        {
            xValue = xValue;
        }
        int posValue = 0;
        while(xValue > 0)
        {
            posValue = xValue%10;
            xValue = xValue/10;
            result = result*10+posValue;
        }
        
        if(x < 0)
        {
            result =  0-result;
        }
        if(result >= INT_MAX)
        {
            return 0;
        }
        
        if(result <= INT_MIN)
        {
            return 0;
        }
        return result;
    }
};
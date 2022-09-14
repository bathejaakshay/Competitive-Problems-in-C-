## Power Exponentiation

#### [1. 50. Pow(x, n)](https://leetcode.com/problems/powx-n/)
**Approach log(n) time**  

- if n is even then we compute x^n we compute it like (x^(n/2))^2) So it is T(n) = T(n/2) + 1
-  else we compute x* (x^(n/2))^2

```
double power(double x, long long n){
    
    if(n==0) return 1;
    if(n==2) return x*x;
    if(n%2==0) return power(power(x, n/2), 2);
    else return x*power(power(x,n/2),2);
    
}

class Solution {
public:
    double myPow(double x, int n) {
        int flag=0;
        long long nn;
        if(n<0) {
            flag=1;
            nn=abs(n); 
            
                }
        else nn=n;
        double ans = power(x, nn);
        if(flag) return 1/ans;
        return ans;
    }
};
```

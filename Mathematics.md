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

# Salesforce Q1. Digits whose alphabetic representations are jumbled in a given string

Given a string S of length N which is the English representation of any number of digits in the range `[0 – 9]` in jumbled format. The task is to find the digits from this representation. 
Note: Print digits in any order

**Approach**
- Observation is required that each string representation of even numbers has one char that doesnt come in any other string representation.
- But it is not true for odd numbers.
- Represent each number by a char which comes in its string representation.
- Mantain an array to count the occurence of each 0 to 9 representator.
- Traverse through the string and increment count of the repsective representator.
- Finally for each odd number say x substract the count of the numbers whose string representation has the representator x in it. e.g seven's representator is 's'
- So `count[7] = count[7]- count[6]`

```
void solve2(string s){
    //represent each number by its unique char, there exist unique char for even numbers
    // for odd number choose the most less repeating one and substract the count of repeating chars from it

    vector<int> mp(10,0);
    for(int i=0; i<s.length(); i++){
        if(s[i] == 'z'){
            mp[0]++;
        }
        if(s[i] == 'w'){
            mp[2]++;
        }
        if(s[i] == 'u'){
            mp[4]++;
        }
        if(s[i] == 'x'){
            mp[6]++;
        }
        if(s[i] == 'g'){
            mp[8]++;
        }
        if(s[i] == 'o'){
            mp[1]++;
        }
        if(s[i] == 'h'){
            mp[3]++;
        }
        if(s[i] == 'v'){
            mp[5]++;
        }
        if(s[i] == 's'){
            mp[7]++;
        }
        if(s[i] == 'i'){
            mp[9]++;
        }

    }
    mp[1] -=(mp[0]+mp[2] + mp[4]);
    mp[3] -=(mp[8]);
    mp[7] -=(mp[6]);
    mp[9] -=(mp[5] + mp[6] + mp[8]);
    for(int i=0; i<10; i++){
        if(mp[i]>0){
            int x = mp[i];
            while(x>0){
                cout<<i;
                x--;
            }
        }
    }
    return;
}

```

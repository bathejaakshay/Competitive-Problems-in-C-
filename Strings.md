#### [1. Longest Palindrome String](https://leetcode.com/problems/longest-palindromic-substring/submissions/)
**Main Idea:**
Naive Approach:  
1.We will go through all index pairs O(n^2) * see if those are palindrome and keep only largest palindrome O(n) = O(n^3)

DP:  
1. Create a 2-D bool Dp array to represent indices i&j of the string where j>i and dp[i][j] is true if substring (i to j) is palindrome else false;
2. Now go through pairs by traversing substrs of length 1 , then length 2 ... length n
3. For each pair check if s[i] == s[j] and dp[i+1][j-1] is true. i,e current i and j are same and remaining substring is palindrome. if current palindrome length is greater than the maximum then store current index pairs in var a,b;
4. else dp[i][j]= false;

```
 string longestPalindrome(string s) {
        vector<vector<int>> dp(s.length(), vector<int>(s.length(), true));
        int a=0,b=0,curr=0;
        int k;
        for(int i=0;i<s.length()-1;i++){
            k=0;
            for(int j=i+1;j<s.length();j++){
                string ss = (dp[k+1][j-1]==true)?"true":"false";
                cout<<" i,j, k= "<<i<<","<<j<<","<<k<<" s[k]="<<s[k]<<" s[j]="<<s[j]<<" "<<ss<<endl;
                if(s[k] == s[j] && dp[k+1][j-1]){
                    
                    if(curr< j-k) {
                        curr = b-a+1;
                        a=k;
                        b=j;
                    }
                }
                else{
                    dp[k][j] = false;
                }
                k++;
            }
        }
        return s.substr(a, b-a+1);
    }
```

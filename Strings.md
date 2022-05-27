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
#### [2. Generating all balanced paranthesis](https://leetcode.com/problems/generate-parentheses/)
**Problem Statement:** Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.  
**Main Idea:**  
1. Clearly it is a combination problem so we will use backtracking.
2. we will apply it by keeping track of n no. of left paranthesis and m no. of right paranthesis. (rememenber n should always be < m)
3. now s.push_back('(') -> recurse -> s.pop_back()
4. s.push_back(')') -> recurse -> s.pop_back()

```
void gp(int n, int m,string s, vector<string> &ans){
        string temp=s;
        
        if(n==0 && m==0){
            ans.push_back(s);
        }
        if(m<n) return ;
        if(n<0 || m<0) return;
        s.push_back('(');
        gp(n-1,m,s,ans);
        s.pop_back();
        s.push_back(')');
        gp(n,m-1,s,ans);
        s.pop_back();
        return;
        
    }
    vector<string> generateParenthesis(int n) {
        
        vector<string> ans;string s="";
        gp(n,n,s,ans);
        return ans;
    }
```

---

### [3. Count number of Palindromic strings](https://leetcode.com/problems/palindromic-substrings/submissions/)
**Main Idea:**  
1. Using 2D DP bool array to represent if d[i][j] i.e substring i to j is a palindrome or not
2. The traversal is like 0,1 1,2 2,3 .. then 0,2 2,4 .. so substrings of length 1,2,3 ...

```
class Solution {
public:
    int countSubstrings(string s) {
    
    vector<vector<bool>> dp(s.length(), vector<bool>(s.length(),true));
       int ans=0;
       if(s.length()==0) return 0;
       if(s.length()==1) return 1;
        int k;
     for(int i=0; i<s.length();i++){
         ans++;
         dp[i][i] = true;
         k=0;
         for(int j=i+1; j<s.length();j++){
             if(s[k]==s[j] && dp[k+1][j-1]){
                 ans++;
                 dp[k][j]=true;
             }
             else{
                 dp[k][j] = false;
             }
             k++;
         }
     }
       return ans;
    }
};
```
---

#### 4. Pattern Matching
Give a string of length N and a pattern of len M find the starting indices of all the matching patterns in the text.  
e.g TXT = "abccdcabc"  
     pattern = "abc"    
     Output = 0 6  
     
**Naive Approach** : Sliding Window i.e iterate through a window of size pattern in text and compare the window with the pattern.  
Time Complexity = O((N-M+1) * M)  

**Naive Approach 2 **: If the pattern consists of unique char then no need to traverse through each window, whenever there is a mismatch in the window [i,j] say at k
then shift the next window to [k+1, j+k] (i.e no need to look at chars at i+1 till k as they will also mismatch if we shift the window)
Time Complexity = O(N)

**Rabin Carp**: We still use sliding window. The difference is that we precompute the hash of pattern and compare its hash with all the window's hash and compare the pattern only when the hash matches. It is useful in the case of multiple patterns.  
Time Complexity = O((N-M+1) * M).

**KMP**

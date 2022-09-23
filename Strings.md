#### [1. Longest Palindrome String](https://leetcode.com/problems/longest-palindromic-substring/submissions/)
**Main Idea:**
Naive Approach:  
1.We will go through all index pairs O(n^2) * see if those are palindrome and keep only largest palindrome O(n) = O(n^3)

**Iterative: Intuitive**
- What is a better approach to tackle if a string is palindrom? 
- Either to start at the ends and keep match till middle
- or start at middle and keep matching till end. In this case starting at middle helps reduce the Time complexity.
- For each index in a string we consider it as the center of the palindromic substring and expand outwards to find maxlen with the current index as center in the palindromic substring. 
- This takes O(n^2) time in total. 
- Although there is a little catch for even palindromic substring, the centre are two indices. and then we expand outwards.
- This approach is much better.

```
string longestpalin(string &s){
    // take a string and its reverse and find the LCS - this will not work in case of substring
    string a = s;
    
    
    //traverse through each char in string and consider it as center of the palindromic string
    // we need to take two cases even length palindrome and odd length
    int max_len=0,len=0, start=0;
    for(int i =0; i<s.length(); i++){
        //odd length
        int l=i, r=i;
        while(l>=0 && r<s.length() && s[l] == s[r]) {
            len = r-l+1;
            if(len>max_len){
                max_len = len;
                start = l;
            }
            l--;
            r++;
            
        }
        
        //even length
        
        l = i; r=i+1;
        while(l>=0 && r<s.length() && s[l] == s[r]){
            len = r-l+1;
            if(len>max_len){
                max_len = len;
                start = l;
            }
            l--; r++;
        }
    }
    return s.substr(start, max_len);
}
```

DP tough:  
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

## 4. Pattern Matching
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

#### KMP 
In this approach we make use of LPS Array(Longest Proper Prefix and Suffix). This is used so that in a window while we are matching a pattern to a text whenever we get a mismatch we dont start matching from the beginning in the pattern, instead we check which was the substring in the current pattern which was proper prefix as well as suffix and start matching after that index.

**Longest Proper Prefix Suffix Array**

e.g string s = "abcabjeabc"
          LPS = {0,0,0,1,2,0,0,1,2,3}
          Length of LPS for first char is always zero as we take proper prefix i.e before current word. For string aba : LPS is 2 because prefix a matches with suffix a.
         
```
vector<int> LPS(string s){

vector<int> lps_arr;
lps_arr[0] =0;

int len=0;
int i=1;
while(i<s.length()){
 if(s[i] == s[len]){
  len++; 
  lps_arr[i] = len;
  i++;
 }
 else{
  if(len==0) {
    lps_arr[i] = 0;
    i++;
  }
  else{
    len = lps_arr[len-1];  //If s[i] doesnt match with current len i.e s[len] then se what was the length of previous longest proper pref suff lps_arr[len-1] and then see if s[i] matches with char at that len.
  }
 }
}
return lps_arr;
}

          
```
      
          
Now, Once the LPS_array is constructed we can search for the indices of pattern in the text.  
1. The main idea is that start with i=0,j=0 where i iterate on the given text and j iterate over the pattern given.  
2. Now while the pattern and text char matches increment i and j
3. Whenever a mismatch occurs look for the lps[j-1] i.e the len of the longest proper prefix which is also suffix till j-1. 
4. The intution of doing so is that consider a string text = "abacef" and pattern="abaxy" now when mismatch at i = 3 and j=3 occurs ('c'!='x')
5. We see the LPS of string aba because if it is greater than 0 then we dont need to compare that many char in pref now LPS[2] = 1 i.e 'a' in pattern so we can start comparing 'b' of pattern with 'x' of text as their prefix already matches. (Good logic NO?)

6. Whenever during the iteration you find that j has reached patter.length() i.e pattern found then append i-pattern.length() to ans and again update j=lps[j-1] so that we donot have to start again with j=0.

```

vector<int> KMP(string text, string pattern){
    
//Construct lps for the pattern first.
vector<int> lps = LPS(pattern);
vector<int> ans;
int i=0,j=0;
whlie(i<text.length()){

 while(text[i] == pattern[j]){
    i++;j++;
 
 } 
 if(j == pattern.length()){
    ans.push_back(i-pattern.length()); // appending ans
    j=lps[j-1]; //assign longest proper prefix which is also a suffix of string pattern to j
    
 }
 
 else if(i<text.length() && text[i] != pattern[j]){
   
   if(j==0) i++;  //if pattern iterator is still at start just increment text iterator.
   else{
     j = lps[j-1]; //else find lps[j-1] and assign it to j
   }
 }
 

}
  return ans;
}

```

---

#### [5. Find Palindrome With Fixed Length](https://leetcode.com/problems/find-palindrome-with-fixed-length/)
Given an integer array queries and a positive integer intLength, return an array answer where `answer[i]` is either the `queries[i]th` smallest positive palindrome of length intLength or `-1` if no such palindrome exists.  
A palindrome is a number that reads the same backwards and forwards. Palindromes cannot have leading zeros.  

 
```
Example 1:

Input: queries = [1,2,3,4,5,90], intLength = 3
Output: [101,111,121,131,141,999] : The 1st palindrome number of length 3 is 101, 2nd is 111 and so on.
Explanation:
The first few palindromes of length 3 are:
101, 111, 121, 131, 141, 151, 161, 171, 181, 191, 202, ...
The 90th palindrome of length 3 is 999.
```
**Approach :**
1. The approach is easy once you think about it.
2. First we need to understand then we just need to find the half number as the other half would be repeating for the palindrome.
3. So cal half = (len+1)/2
4. Now find the min and max number with this half i.e for two digits half=2 min = 10 and max=99
5. so start = 10^(half-1), end = 10^(half)-1
6. now the kth palindrome of length len is: its first half will be start+k-1
7. If the len is odd then last digit of half wont be reversed else the whole half will be reversed and concatenated with the original half for the ans

```
long long kpalin(int n, int len){
        int half = (len+1)/2;
        int start = pow(10,half-1);
        int end = pow(10,half)-1;
        if(n> end-start+1){
            return -1;
        }
        string front=to_string(start+n-1);
        string f;
        string b;
        if(len%2==1){
            f = front.substr(0,half-1);
            reverse(f.begin(),f.end());
            return stoll(front+f);
        }
        else{
            f = front;
            reverse(f.begin(),f.end());
            return stoll(front+f);
        }
    }
    
    vector<long long> kthPalindrome(vector<int>& queries, int intLength) {
        vector<long long> ans;
        for(int &q:queries){
            ans.push_back(kpalin(q,intLength));
        }
        return ans;
    }
```

---

#### [6. Shortest Common Supersequence](https://www.codingninjas.com/codestudio/problems/shortest-supersequence_4244493?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=1)

**Approach**
1. Shortest Common supersequence is the concatenation of two substrings in which LCS comes only once.
2. So after creation of LCS table, we can perform following operations
3. `if (a[i-1] == b[j-1])` then add the char in the result string and do i--, j--
4. else `if(dp[i-1][j] > dp[i][j-1])` then move to the maximum one of those add the char which we are not observing anymore.

```
string lcs(string a, string n){
    
    vector<vector<int>> dp(a.length()+1, vector<int>(n.length()+1,0));
    
    for(int i=1; i<=a.length(); i++){
        for(int j=1; j<=n.length(); j++){
            if(a[i-1] == n[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
   int i=a.length(), j=n.length();
   string ans="";
    while(i>0 && j>0){
        if(a[i-1] == n[j-1]){
            ans = ans + a[i-1];
            i--;j--;
        }
        else{
            if(dp[i-1][j] > dp[i][j-1]){
                ans = ans+ a[i-1];
                i--;
            }
            else{
                ans = ans + n[j-1];
                j--;
            }
        }
    }
    while(i>0){
        ans+=(a[i-1]);
        i--;
    }
    while(j>0){
        ans+=(n[j-1]);
        j--;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
```
---

#### [7. Min number of swaps to bring all Red balls together](https://algo.monster/problems/min_adj_swaps_to_group_red_balls)

There are N balls positioned in a row. Each of them is either red or white . In one move we can swap two adjacent balls. We want to arrange all the red balls into a consistent segment. What is the minimum number of swaps needed?  

Given string S of length N built from characters "R" and "W", representing red and white balls respectively, returns the minimum number of swaps needed to arrange all the red balls into a consistent segment. If the result exceeds 10^9, return -1.  

**Approach** 
- The optimal approach is to bring the all red balls to the middle of first and last red ball.
- We use 2 pointer approach to do so.
- We precompute the total occurence of Red balls which help us compute the white in any window starting and ending with red ball in one operation.
- each find we find new start red and end red and compute white balls as swap.

```
int min_swaps(std::string s) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int count_red=0;
    for(int i=0; i<s.length(); i++){
        if(s[i] == 'R') count_red++;
    }
    int count=0;    
    int i=0, j = s.length()-1;
    while(i<j){
        if(s[i] == s[j] && s[i] == 'R'){
            count += j-i-1-(count_red-2);
            count_red-=2;
            i++;
            j--;
        }
        while(s[i]=='W') i++;
        while(s[j] == 'W') j--;
    }
    return (count<0)?-1:count;
}
```

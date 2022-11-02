## Passing 2D array as pointer to a function in C.

Here we will look at how to implement 2d DP using arrays.


#### [Coin Change 2](https://leetcode.com/problems/coin-change-ii/description/)  
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.  

Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.  

You may assume that you have an infinite number of each kind of coin.  

The answer is guaranteed to fit into a signed 32-bit integer.  
**Approach**  
- For 2D dp we create an array of pointers and pass it to the function. 
- For 2D array of pointers we need not declare size of second dimension during declaration.
- Assign memory to each pointer in 1st dimension.
- the logic of coin change 2 is same.

```
int coinchange(int i, int amount, int *coins, int coinsSize, int **arr){
    if(amount == 0) return 1;
    if(i>=coinsSize || amount<0) return 0;
    if(arr[i][amount]!=-1) return arr[i][amount];
    int left = coinchange(i, amount-coins[i], coins, coinsSize, arr);
    int right = coinchange(i+1, amount,coins, coinsSize, arr);
    return *(*(arr+i) + amount) = left + right;   
}
int cmp(const void *a, const void *b){
return (*(int *)a - *(int*)b);
}
int change(int amount, int* coins, int coinsSize){

qsort(coins, coinsSize, sizeof(int), cmp);
second = amount+1;
int *dp[coinsSize];
for(int i=0; i<coinsSize; i++){
    dp[i] = (int *)malloc((amount+1) * sizeof(int));
}
for(int i=0; i<coinsSize; i++){
    for(int j=0; j<amount+1;j++){
        dp[i][j] = -1;
    }
}
return coinchange(0, amount, coins, coinsSize, dp);
}
```
---

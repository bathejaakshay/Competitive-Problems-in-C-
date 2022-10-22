All these builting functions reside in stdio.h

#### __builtin_pop_count(x)
Count number of setbits (1's) in an integer  
**for long long type x use: __builtin_pop_countll(x)  
e.g cout<<__builtin_pop_count(10) 
O/P : 2

#### __builtin_parity(x)

This is used to check the parity of a number. This function returns zero if x has odd parity and one if x has even parity.
Odd parity means, odd number of set bits (1).  

Similarly you can use **__builtin_parityl(x) & __builtin_parityll(x)** for long and long long data types.

####  __builtin_clz(x)

This is used to count the number of leading zeros in the binary representation of integer x. It accepts only unsigned int values

#### __builtin_ctz(x)

This is used to count the number of trailing zeros in the binary representation of integer x.  

Note: Similarly you can use **__builtin_ctzl(x) & __builtin_ctzll(x)** for long and long long data types.


#### __gcd(a,b)
Returns 0 if both a and b are zero otherwise returns gcd of a and b

Present in <numeric>
TC: O(log(n))
  

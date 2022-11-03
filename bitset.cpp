## To convert decimal into binary array effecient then bool array and vector

```
int main(){
bitset<8> b(129); // Represent decimal to binary in 32 bit representation
    cout<<b<<endl;
    b.set(0,0); //set bit 0th bit (LSB) to 0
    cout<<b<<endl;
    cout<<b.count()<<endl; // count number of set bits
}
```

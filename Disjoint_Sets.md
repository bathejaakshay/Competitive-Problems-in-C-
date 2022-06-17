#### 1. Union and Find DS
**Motivation**  
1. Useful when we want to divide the universe into different disjoint sets such that no two components form different sets can ever join.
2. A lot of applications like in finding number of Connected Components and MST.
3. This data structure make use of two simple functions namely:
4. Find(x,y) : Finds if both x and y belong to same set.
5. Union(x,y) : Combined both x and y. It follows a tree structure, so by combining we mean make set y a child of x. or vice versa based on their ranks.
6. Parent[x] : We maintain Parent array to represent tree structure. Intially all nodes are parents of itself.
7. Rank[x] : Rank defines the height of the tree x.
8. Our Ulimate goal is to implement union and find with least TC.
9. Using adjlist Union and find both take O(n) time, while using adjency matrix union takes O(n) and find takes O(1) 
10. Using ranking mechanism we make sure that we dont traverse more than the height of the tree. so O(logn)
11.Finally Using Path compression technique Our amortized complexity boils down to O(c) where c is alph(n) which is less than 4.

**Path Compression**
1. In Path Compression whenever we perform find(x) then while finding the representative (root) of the tree we assign all the ancestors of x directly to the root. This compresses the path.

```

int Find(int x, vector<int> &parent){
    if(x == parent[x]){
        return x;
    }
    parent[x] = Find(parent[x], parent); // Path Compression
    return parent[x];
}


void Union(int x, int y, vector<int> &parent, vector<int> & rank){
    int a = Find(x, parent);
    int b = Find(y, parent);

    if(a!=b){
        if(rank[a]>rank[b]){
            parent[b] = a;
        }
        else if(rank[a]<rank[b]){  // Union by rank
            parent[a] = b;
        }
        else if(rank[a] == rank[b]){
            parent[b] = a; 
            rank[a]++;
        }
    }
}


```

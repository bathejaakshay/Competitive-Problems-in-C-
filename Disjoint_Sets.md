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

---

#### [2 Redundant Connection](https://leetcode.com/problems/redundant-connection/)
**Approach**  
1. For each edge find if the two vertices are already connected or not.
2. If not then union them
3. If they are then that is our ans.

`TC : O(N)`
```
int Find(int u, vector<int> &parent){
    if(parent[u] == u){
        return u;
    }
    parent[u] = Find(parent[u], parent);
    return parent[u];
}

void Union(int a, int b, vector<int> &parent, vector<int> &rank){
    if(rank[a]<rank[b]){
        parent[a] = b;
    }
    else if(rank[a]>rank[b]){
        parent[b] = a;
    }
    else{
        parent[b] = a;
        rank[a]++;
    }
}

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> parent(edges.size()+1);
        for(int i=1; i<edges.size(); i++){
            parent[i] = i;
        }
        vector<int> rank(edges.size()+1,1);
        int a,b;
        for(int i=0; i<edges.size(); i++){
            a = Find(edges[i][0], parent);
            b = Find(edges[i][1], parent);
            if(a==b){
                return edges[i];
            }
            Union(a,b,parent,rank);
     
        }
        return {-1,-1};
    }
};
```
---
#### [3. Graph a valid Tree]()
**Approach**
1. Same using union and find if there is a cycle.
2. and maintain a count of componenets, intializing with n comp and doing n-- when we union two comp.
3. If Finally n>1 then it is not a tree.
4. Else it is as it is connected and acyclic.

```
int find(int a, vector<int> &parent){
    if(a==parent[a]) return a;
    parent[a] = find(parent[a], parent);
    return parent[a];
}
void unions(int a, int b, vector<int> &parent, vector<int> &rank){
    if(rank[a]> rank[b]){
        parent[b] = a;

    }
    else if(rank[a]<rank[b]){
        parent[a] = b;
    }
    else {
        parent[b]=a;
        rank[a]++;
    }
}

bool checkgraph(vector<vector<int>> edges, int n, int m)
{
    int comp = n;

        vector<int> parent(n);
        for(int i=0; i<n; i++){
            parent[i]=i;
        }
        vector<int> rank(n,1);
        int a,b;
        for(int i=0; i<edges.size(); i++){
            a = find(edges[i][0], parent);
            b = find(edges[i][1], parent);
            if(a==b) return false;
            unions(a,b,parent, rank);
            comp--;
        }
        if(comp == 1){
            return true;
        }
        return false;
    
    // write your code here
}
```

---
#### [4. Most Stones Removed with Same Row or Column VV.IMP Google](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/)
On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at most one stone.  

A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.  

Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone, return the largest possible number of stones that can be removed.  

**Approach Union Find**
1. We need to find total number of connected components.  Our ans will be total stones - no.of components.
2. All the points which has common row_index or column_index comes under one component.
3. Now It is a little different Union-Find from what we have seen as we dont apply it in the conventional way
4. We use unordered_map for the parent data structure and we dont use rank.
5. Also all the x-coordinate and y-coordinate represent a different node in our graph and shall be identified differently while doing union that is why we add 100001 to y-coordinate before UNION or we can also do `~y-coordingate` i.e take ones complement. This is because `0<x-coorindate, y-coordinate<10^4`
6. In the find function, while find the parent of node u if node is not present in the unordered map parent then we add it mark it as a new component
7. We do this for x and y-coordnate
8. Now if parent of x and parent of y are different then it means they belong to two different components but they need to be unionized hence we decrement the connected componenets by 1 and do `parent[parent[y]] = parent[x]` 
9. Final ans is total stones - no. of connected components.

```
int find(int u, unordered_map<int,int> &parent,int &ans){
    if(parent.find(u)==parent.end()) {
        parent[u] = u;
        ans++;
        return u;
    }
    return (u==parent[u])? u: parent[u]=find(parent[u], parent, ans);
}
void uni(int u, int v, unordered_map<int,int> &parent,int &ans){
    u = find(u, parent, ans);
    v = find(v, parent, ans);
    if(u!=v){
        parent[v] = u;
        ans--;
    }
    return;
}

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {

        int n = stones.size();
        int ans=0;
        unordered_map<int,int> parent;
        for(int i=0; i<n; i++){
            int x = stones[i][0];
            
            int y = stones[i][1] + 100001;
            uni(x,y,parent, ans);
            
        }
        
        return n - ans;
        
        
    }
};
```

TC: O(N), SC: O(N)

---

#### [5. Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/)
There are n computers numbered from 0 to n - 1 connected by ethernet cables connections forming a network where `connections[i] = [ai, bi]` represents a connection between computers ai and bi. Any computer can reach any other computer directly or indirectly through the network.  

You are given an initial computer network connections. You can extract certain cables between two directly connected computers, and place them between any pair of disconnected computers to make them directly connected.  

Return the minimum number of times you need to do this in order to make all the computers connected. If it is not possible, return -1  


**Approach : Union Find**  
1. Using Union Find, Count the total number of connected components and total number of extra edges(edges that introduce cycle within a component)
2. Number of edges required to make all components connected = no. of connected components - 1

```
int find(int i, vector<int> &parent){
    if(i == parent[i]) return i;
    return parent[i] = find(parent[i], parent);
}
void uni(int u, int v, int &comp, int &ade, vector<int> &parent){
    u = find(u, parent);
    v = find(v, parent);
    if(u==v){
        ade++;
    }
    else{
        comp--;
        parent[v] = u;
    }
}

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        vector<int> parent(n);
        int comp = n; // Total Number of connected components
        int ade= 0; // Total Number of additional edges
        for(int i=0; i<n; i++){
            parent[i] = i;
            
        }
        for(int i=0;i<connections.size(); i++){
            int u = connections[i][0];
            int v = connections[i][1];
            uni(u,v,comp,ade, parent);
        }
        if(comp-1 > ade ) return -1;
        return comp-1;
        
        
    }
};
```

---

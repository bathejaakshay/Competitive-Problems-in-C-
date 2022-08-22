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

#### [6. Satisfiability of Equality Equations](https://leetcode.com/problems/satisfiability-of-equality-equations/)
You are given an array of strings equations that represent relationships between variables where each string `equations[i]` is of length 4 and takes one of two different forms: `"xi==yi" or "xi!=yi"`.Here, xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.  

Return true if it is possible to assign integers to variable names so as to satisfy all the given equations, or false otherwise.

**Approach : Union Find**

1. We will have 26 nodes or connected components initially.
2. Firstly go over each equality equations "==" and put the left and right variables in the same component.
3. Then go over all inequality equation "!=" and check if left and right variable belong to different component.
4. If not then return false.

```
int find(int i, vector<int> &parent){
    return (parent[i] == i)?i:parent[i] = find(parent[i], parent);
}

void uni(int u, int v, vector<int> &parent){
    u = find(u, parent);
    v = find(v, parent);
    
    if(u!=v){
        parent[v] = u; 
    }
}
class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        vector<int>parent(26);
        for(int i=0; i<26; i++){
            parent[i] = i;
        }
        
        for(int i=0; i<equations.size(); i++){
            int u = equations[i][0]-'a';
            int v = equations[i][3] - 'a';
            if(equations[i][1] == '='){
                uni(u,v, parent);
            }
        }
        
        for(int i=0; i<equations.size(); i++){
            int u = equations[i][0]-'a';
            int v = equations[i][3] - 'a';
            if(equations[i][1] == '!'){
                if(find(u,parent)==find(v, parent)) return false;
            }
        }
     return true;   
    }
};
```

#### [7. Accounts Merge](https://leetcode.com/problems/accounts-merge/)

Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.  

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.  

After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.  

 
```
Example 1:

Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
```

**Approach : Union Find** 
- Two things to understand about Union find pattern
- Is it a question of grouping? or finding cycle or finding connected components
- Once you have identified the pattern then look for, what will be the nodes and what will be its parent or representative
- For e.g the nodes in this question are all the email ids and the representative will also be an email string which will represent them all.

1. Firstly intialize all the parents of each mail to itself and keep record of the owner of each mail.
2. For each email of a particular user make the first email parent of all other emails. This will allow the mails to serialize and have one single parent for all emails corresponding to the user.
3. Now Create another hashmap representing the parent email as key as all its child emails as values (sorted)
4. Now just create the final ans using the hashmap created in the previous step and the owner hashmap.

```
string find(string x, unordered_map<string, string> &mp);
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        // Two things to understand about Union find pattern
        // Is it a question of grouping? or finding cycle or finding connected components
        // Once you have identified the pattern then look for, what will be the nodes and what will be its parent or representative
        // For e.g the nodes in this question are all the email ids and the representative will also be an email string which will represent them all.
        
        
        unordered_map<string, string> parent; // To keep record of the representative of a particular email.
        unordered_map<string, string> owner; // To keep record of the owner/user of a particular email.
        
        unordered_map<string, set<string>> unions; // This will be our final email hashmap representing the representative email of a user and its correspong all emails.
          
        vector<vector<string>> ans;
        // Initialize parent and owner     
        for(int i=0; i<accounts.size(); i++){
            for(int j=1; j<accounts[i].size(); j++){
                parent[accounts[i][j]] = accounts[i][j];
                owner[accounts[i][j]] = accounts[i][0];
            }
        }
        
        // Union each mail in each account
        for(int i=0; i<accounts.size(); i++){
            for(int j=2;j<accounts[i].size(); j++){
                string x = find(accounts[i][j-1], parent);
                string y = find(accounts[i][j], parent);
                if(x!=y)
                    parent[y] = x;
            }
        }
        
        // Now I want a single ds which consists of all temp/child emails related to the primary/parent one
        for(int i=0; i<accounts.size(); i++){
            for(int j=1; j<accounts[i].size(); j++){
                unions[find(accounts[i][j], parent)].insert(accounts[i][j]);
            }
        }
        
        // Now I want to obtain the final ans in the required format using the owner ds.
        
        for(auto it = unions.begin(); it!=unions.end(); it++){
            vector<string> cand(it->second.begin(), it->second.end());
            
            cand.insert(cand.begin(), owner[it->first]);
            
            ans.push_back(cand);
        }
        return ans;
    }
};

string find(string x, unordered_map<string, string> &mp){
    return (x == mp[x])? x : mp[x] = find(mp[x],mp);
}
```

---

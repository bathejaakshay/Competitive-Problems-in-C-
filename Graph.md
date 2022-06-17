#### [1. Find Cycle in Directed Graph/ Course Schedule](https://leetcode.com/problems/course-schedule/)
**Main Idea:**  
1. We will use DFS for the cycle detection. It is not as easy as in the undirected graph in which we just check visited array and parent (if a child is already visited and is not my parent then it is a cycle)
2. In Directed graph we check for backedge. We do this by maintaining recstk array which is a bool array represented which all vertex are currently in recstk. 
3. Now for a node say x there exists a back edge if its neighbour node say y is already visited and is already in the recstk i.e recstk[y] = 1;
4. Do remember to make recstk[x] = false whenever x is popped off the recurrsion stack.
5. The following code is primarily the solution for course-schedule problem. In this if we have edge (0,1) this represent that we can take course 0 if we already have taken course 1.
6. So to take all courses, there shouldn't exist any cycle.
```
void add_edge(vector<vector<int>> &adjlist, vector<int> &prereq){
    adjlist[prereq[0]].push_back(prereq[1]);
    
}

bool dfs(vector<vector<int>> &adjlist, vector<bool> &visited, vector<bool> &recstk, int source){
    for(int &i:adjlist[source]){
        if(!visited[i]){
            visited[i] = true;
            recstk[i] = true;
            if(dfs(adjlist, visited, recstk, i)==false) return false;
        }
        else if(recstk[i] == true){ //if node is already visited and is in rec stack then back edge hence cycle hence not possible to schedule all courses so false
            return false;
        }
            recstk[i] = false;
    }
    return true;
}
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adjlist(numCourses);
        vector<bool> visited(numCourses);
        for(int i=0; i<prerequisites.size();i++){
            add_edge(adjlist,prerequisites[i]);
        }
        vector<bool> recstk(numCourses);
        
        for(int i=0; i<numCourses; i++){
            if(!visited[i]){
                visited[i] = true;
                recstk[i] = true;
                if(dfs(adjlist,visited,recstk,i) == false){
                    return false;
                }
                recstk[i] = false;
            }
        }
        
        return true;
        
    }
};
```
---

#### [2. Cycle Detection in UnDirected Graph](https://www.codingninjas.com/codestudio/problems/1062670?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=0)
**Approach:**
1. We will look at BFS approach as DFS is relatively easy, will also mention the approach for DFS.
2. Cycle Detection is possible in undirected graph by looking at the visited array.
3. For an element say x we are traversing through its neighbours:
4. Now say its neighbour y is already visited i.e visited[y]=1, now if y is not the parent of x then this is a cycle.
5. We can say that there is always a cycle when a visited node is visted again and it is not a parent node.
6. In BFS we use hashmap to keep track of parents of the node.
```
e.g 
graph:- 

1-2 (In this graph node 1 will be visited twice, first by starting with 1 and next time as a neighbour of 2 but this is not a cycle as 1 is the parent of 2)

1-2-3-1 is the cycle
```

```
#include<bits/stdc++.h>
void addEdge(vector<vector<int>> &adjlist, vector<int> &edge){
    adjlist[edge[0]-1].push_back(edge[1]-1);
    adjlist[edge[1]-1].push_back(edge[0]-1);
}
string cycleDetection (vector<vector<int>>& edges, int n, int m)
{
    vector<vector<int>> adjlist(n);
    for(int i=0; i<edges.size();i++){
        addEdge(adjlist, edges[i]);
    }
    vector<bool> visited(n,false);
    queue<int> q;
    unordered_map<int,int> par;
    for(int i=0;i<n;i++){
        if(!visited[i]){
            if(q.empty()){
                q.push(i);
            }
            par[i]=-1;
            visited[i]= true;
            while(!q.empty()){
                int x = q.front();
                q.pop();
                for(int &j:adjlist[x]){
                    
                    if(!visited[j]){
                        visited[j]=true;
                        par[j]=x;
                        q.push(j);
                    }
                    else{
                        if(j!=par[x]){
                            return "Yes";
                        }
                        
                    }
                }
            }
        }
    }
    return "No";
}

```

**DFS Approach:**
1. DFS approach is relatively simple as we dont need to use extra hashmap. We just pass the parent node value in the dfs recursive call.
2. The rest of the logic is same, if the node is visited twice and is not same as the parent of its neighbour node then there is a cycle.

```
void addEdge(vector<vector<int>> &adjlist, vector<int> &edge){
    adjlist[edge[0]-1].push_back(edge[1]-1);
    adjlist[edge[1]-1].push_back(edge[0]-1);
}
bool dfs(vector<vector<int>> &adjlist, int source, int parent, vector<bool> &visited){
    //Cycle Detection using DFS
    for(int &i:adjlist[source]){
        if(!visited[i]){
            visited[i]=true;
            if(dfs(adjlist, i, source, visited)){
                return true;
            }
        }
        else if(i!=parent){
            return true;
        }
        
    }
    return false;
}
string cycleDetection (vector<vector<int>>& edges, int n, int m)
{
    vector<vector<int>> adjlist(n);
    for(int i=0; i<edges.size();i++){
        addEdge(adjlist, edges[i]);
    }
    vector<bool> visited(n,false);
// Cycle Detection Using DFS
    for(int i=0;i<n;i++){
        if(!visited[i]){
            visited[i] = true;
            if(dfs(adjlist, i, -1, visited)){
                return "Yes";
            }
        }
    
    }    

    return "No";
}

```

---

#### [3. Topological Sort using BFS Kahn's Algo](https://practice.geeksforgeeks.org/problems/topological-sort/1)
**Approach: Very Easy**
1.After creating an adjacency list, create an indegree vector which keeps note of indeg of each node.
2.Now initially push all nodes in queue whose indeg is 0;
3. Now traverse these nodes in BFS fashion i.e pop 1 by 1 and reduce their neighbours in deg by one and add those neighbours in the queue whose indeg is now 0
4. No need for visited array as there are no cycles and we are traversing nodes one by one.

```
vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    // code here
	    unordered_map<int,int> indeg;
	    for(int i=0;i<V;i++){
	        for(int &j : adj[i]){
	            indeg[j]++;
	        }
	    }
	    queue<int> q;
	    
	    for(int i=0;i<V;i++){
	        if(indeg[i]==0){
	            q.push(i);
	        }
	    }
	    vector<int> ans;
	    while(!q.empty()){
	        int x = q.front();
	        ans.push_back(x);
	        q.pop();
	        for(int &j: adj[x]){
	            indeg[j]--;
	            if(indeg[j]==0){
	                q.push(j);
	            }
	        }
	    }
	    return ans;
	}
```
 **Using DFS**:  
 1. Finding Topological Sort using DFS is also easy.
 2. We just maintain an extra stack and visited array
 3. Simple Call the DFS for all edges.
 4. The moment DFS for that particular node is over add its value into the stack. That way they will be topologicaly sorted in the stack.
---

#### [4. Number of Islands](https://leetcode.com/problems/number-of-islands/submissions/)
**Problem:**  
Given an `m x n` 2D binary grid grid which represents a map of `'1's` (land) and `'0's` (water), return the number of islands.  
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.  

```
Example:  
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
```

**Approach 1**  
1. Broader approach is to apply BFS or DFS to find connected components but the question is how to apply?
2. One way is to convert given grid into an adjlist where each element in the grid is a vertex in an undirected graph.
3. This takes O(m*n) extra space which is alot! and time O(m*n) which is again alot

**Approach 2**  
1. Apply DFS or BFS directly within the graph.
2. For each i&j starting at `[0,0]`
3. mark it as visited by changing char 1 to '*' in place. now traverse in one upward downward forward and backward direction recurrsively.
4. we maintain a counter to count connected components.  


```
void dfs(int i, int j, int m, int n, vector<vector<char>> &grid){
    if(i<0||i>=m||j<0||j>=n||grid[i][j]!='1'){
        return;
    }
    grid[i][j]='*';
    dfs(i-1,j,m,n,grid);
    dfs(i+1,j,m,n,grid);
    dfs(i,j-1,m,n,grid);
    dfs(i,j+1,m,n,grid);
    return;
}
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        char ch='*';
        int count=0;
        for(int i=0;i<grid.size();i++){
            for(int j=0; j<grid[i].size(); j++){
                if(grid[i][j]=='1'){
                    count++;
                    dfs(i,j,m,n,grid);
                }
            }
        }
        return count;
 }
}; 

```
---

#### 5. Shortest Path in DAG
**Approach 1**  
We could use Djikstra or bellmenford but then its TC world be O((V+E)logV)

**Approach 2**
The Better and efficient approach would be through Topological Sorting TC(O(V+E))

**ALGO**
```
ShortestPath(adjlist, src, weight)
	1. Initialize vector<int> dist (size = Vertices, value = INT_MAX)
	2. Set dist[src] = 0
	3. Find Topological Sort T of this graph.
	4. Now For every vertex u of Topological sort T
		For every adjacent v of u:
			if dist[v] > dist[u] + weight(u,v) \\Relax edge (u,v)
				dist[v] = dist[u] + weight(u,v)
				

	5. Done	
```

---


#### [6. Finding MST using Prim's Algo](https://practice.geeksforgeeks.org/problems/minimum-spanning-tree/1)
**Approach:**
1. Simple BFS Traversal using Priority queue as minheap.
2. Start with any node say source and push it in the minheap as a pair (0,src) where 0 is the distance of src from src
3. Now extract min from the priority queue and set the node as finalized and add its distance to the ans. If the node was already finalized then do nothing.
4. Now push its neighbours into the priority queue with their values from the parent node. (Remember while pushing the nodes its possible that it already exists which greater distance in which case we use decrease key but as decrease key is not available in c++, we use a way around through finalized vector.)
5. Repeat step 3,4 until priority queue gets empty. 

```
struct comparator{
    bool operator()(const pair<int,int> &a, const pair<int,int> &b){
        return a.first>b.first;
    }
};
class Solution
{
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    { // adj is an array of vectors of vectors where a[0] = {{1,5},{2,1}} i.e weight of edge (0,1) is 5 and (0,2) is 1.
        // code here
        vector<bool> mset(V,false); // To keep record of all the nodes that have been poped out
        priority_queue<pair<int,int>, vector<pair<int,int>>, comparator> q; // Min heap of pairs , remember that the comparator should be a class with operator() as its function. for minheap return greater.
        int src=0;
        q.push(make_pair(0,src)); // making paris of the next node and the distance to reach there from the current node
        int ans=0;
        while(!q.empty()){ // Simple bfs prims
            auto it = q.top();
            q.pop();
            if(!mset[it.second]){ // As priority queue implementation doesnt have decrease key so we make use of mset which sets for the minimum value of the node and removes the other. We use LAZY Deletion i.e we keep on adding copies of the node with new distances and after extracting it as the minimum distance we mark it as finalized so that we donot process it again.
            ans+=(it.first);
            mset[it.second]=true;
            vector<vector<int>> j = adj[it.second];
            for(int x=0;x<j.size();x++){
                if(!mset[j[x][0]]){
                    q.push(make_pair(j[x][1],j[x][0]));
                }
            }
                
            }
            
        }
        
        return ans;
        
    }
};
```

---

#### [7. Is Graph Bipartite?](https://leetcode.com/problems/is-graph-bipartite/)
**Approach - DFS**
1. A Biparitite graph is one which requires 2 colors to color all vertices. Or we can say we can divide it among two sets such that vertices in a set are not adjacent to each other.
2. Using DFS it is a very simple and intuitive approach. Instead of using boolean visited array, we use int array to represent -> `-1 : not visited`, `0 : first colored`, `1: second colored`.
3. Now we apply DFS and while travering adjacent nodes we color it with different than its parent.
4. If we find the neighbour node is already colored with the same color as the current node then we return false. i.e Graph is not bipartite.

```
bool dfs(vector<vector<int>> &graph, vector<int> &color, int i){
    for(int &j:graph[i]){
        if(color[j] == -1){
            color[j] = abs(1-color[i]);
            if(dfs(graph,color,j)==false) return false;
        }
        else{
            if(color[j] == color[i]){
                return false;
            }
        }
    }
    return true;
}
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> color(graph.size(),-1);
        
        for(int i=0;i<graph.size();i++){
            if(color[i] == -1){
                color[i]=0;
                if(dfs(graph, color, i)==false) return false;
            }
        }
        return true;
    }
};
```

**Approach-BFS**  
1. This approach is also easy. Similar to DFS we maintain a single array to represent color and visited.
2. Now while traversing adjacent nodes we color all its neighbours with different color than the present one. We also check if the neighbour node is already colored with the same color as current one.
3. If yes then return false.

---


#### [8. Dijkstra Using Minheap](https://practice.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1#)
**Approach:**  
1. Using BFS approach starting from source, relax each neighbour edge by checking `d[v] > d[u] + w(u,v)` and pushing into priority queue.
2. We maintain boolean final vector which represents if the vertext is completed or not so that vertex doesnt repeat as we are pushing multiple copies of the vertex.

O((V+E)logV)

```
class Solution
{
    struct compare{
  bool operator()(const pair<int,int> &a, const pair<int,int> &b){
      return a.first>b.first;
  }  
};

	public:
	//Function to find the shortest distance of all the vertices
    //from the source vertex S.
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        // Code here
        vector<int> dist(V,INT_MAX);
        vector<bool> final(V, false);
        dist[S]=0;
        priority_queue<pair<int,int>, vector<pair<int,int>> , Solution::compare> pq;
        // cout<<"pushing"<<endl;
        pq.push(make_pair(0,S));
        // cout<<"S = "<<S<<endl;
        // cout<<"psuhed="<<pq.top().first<<endl;        
        while(!pq.empty()){
            auto it = pq.top();
            pq.pop();
            if(!final[it.second]){
                final[it.second] = true;
                for(int i=0; i<adj[it.second].size();i++){
                    
                    int v = adj[it.second][i][0];
                    int d = adj[it.second][i][1];
                    // cout<<" u = "<<it.second<<" v = "<<v<<" d="<<d<<endl;
                    if(!final[v]){
                        
                        if(dist[v]>dist[it.second] + d){
                            dist[v] = dist[it.second]+d;
                            pq.push(make_pair(dist[v],v));
                        }
                        
                    }
                }
            }
            
        };
        return dist;
    }
};

```
#### [9. Finding Strongly Connected components - Kosaraju's](https://www.codingninjas.com/codestudio/problems/985311?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=1)

**Approach:**
1. Intuition is that we need to apply dfs from sink to source fashion, i.e we start applying it on sink first then its previous nodes.
2. Three step process:
3. First step is to find Topological Order or decreasing order of finish time in dfs. 
4. Second step is to transpose the graph i.e reverse the edges (This will give as sink to source order).
5. Now using the order generated in step 3 do dfs traversal on transpose of the graph. If doing traversal there are no more nodes unvisited then those many nodes are strongly connected. Now choose next node in the order generated in step 3. This node will belong to another strongly connected component.

```
void add_edge(vector<vector<int>> & adjlist, int u,int v){
    adjlist[u].push_back(v);
    return;
}
void dfs(vector<vector<int>> &adjlist, stack<int> & st, int i, vector<bool> &visited){
    for(int &x : adjlist[i]){
        if(!visited[x]){
            visited[x]=true;
            dfs(adjlist, st, x, visited);
            st.push(x);
        }
    } 
    return;
}

void dfs2(vector<vector<int>> &adjlist, vector<bool> &visited, int u, vector<int> &cand){
    for(int &x: adjlist[u]){
        if(!visited[x]){
            visited[x] = true;
            cand.push_back(x);
            dfs2(adjlist, visited, x, cand);
        }
    }
    return;
}
vector<vector<int>> stronglyConnectedComponents(int n, vector<vector<int>> &edges)
{
    // Write your code here.
    vector<vector<int>> adjlist(n);
    vector<vector<int>> alist(n);    
    for(int i=0; i<edges.size(); i++){
        add_edge(adjlist, edges[i][0], edges[i][1]);
        add_edge(alist, edges[i][1], edges[i][0]);
    }
    
    // Step 1 : Using DFS sort in decreasing order of end times
    
    vector<bool> visited(n,false);
    stack<int> st;
    for(int i=0;i<n;i++){
        if(!visited[i]){
            visited[i] = true;
            dfs(adjlist, st, i, visited);
            st.push(i);
        }    
    }
    
    // Step 2: Transpose of the graph or Adjlist Done in A list;
    
    // Step 3: Again dfs in the stack order
    vector<bool> visit(n, false);
    vector<vector<int>> ans;
     while(!st.empty()){
         int u = st.top();
         st.pop();
         if(!visit[u]){
             vector<int> cand;
             visit[u]=true;
             cand.push_back(u);
             dfs2(alist, visit, u, cand);
             ans.push_back(cand);       
         }
         
     }
    return ans;
    
    
}
```

#### [10. Bellman Ford's ](https://www.codingninjas.com/codestudio/problems/2041977?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=1)
**Problem Statement:**  Find a short path from a vertex src to every other vertex if the graph contains negative weights.  
**Approach**:
1. Relax every edge V-1 times because the number of edges in the min path for a source vertex s cant be more than of V-1 length.

**Algo**:
1. Initialize distance vector d of size V with value INT_MAX;
2. set d[src]=0;
3. for i in range(V-1): 
4. 	for every edge(u,v):
5. 		if (d(v)>d(u) + w(u,v)): (Relax edge)
6. 			d(v) = d(u) + w(u,v)		

**Time Complexity O(VE)**

```
int bellmonFord(int n, int m, int src, int dest, vector<vector<int>> &edges) {
    // Write your code here.
    // For V-1 times relax each edge
    vector<int> dist(n, INT_MAX);
    dist[src-1] = 0;
    for(int it=0;it<n-1;it++){
        for(int i=0; i<edges.size();i++){
            int u=edges[i][0], v=edges[i][1], w=edges[i][2];
            if(dist[u-1] == INT_MAX) continue;
            if(dist[v-1] > dist[u-1]  + w ){
                dist[v-1] = dist[u-1] + w;
            }
        }
    }
    if(dist[dest-1]==INT_MAX) return 1000000000;
    return dist[dest-1];
}
```

#### 11. Articulation Points

**Problem:**  
Given an undirected and connected graph, articulations points are the set of those vertices, removal of which divides the graph into more than 1 connected components.

**Naive Approach:**  
We Try removing each vertex and find number of connected components using kojaru's or simple dfs or bfs. `TC O((V+E)*(V+E))`. 

**Little Efficient: DFS TREE**:
When we traverse a graph using dfs we obtain a dfs root tree. i.e starting from a vertex say "src" if I visit its neighbours in a dfs fashion and comeback to src and look for other neighbours of it. Then that means dfs has multiple children.  
<figure>
<center><img src="https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/gfg3.png?raw=True" alt="drawing" width="400"/></center>
</figure>

1. for each vertex find its dfs tree and see if the root has more than 1 child. If yes then it is an articulation point.
**TC** : O(V(V+E))

**Second Efficient Approach**:
We first construct a directed DFS tree. For root node we know if there exist more than one child then it is an articulation point. Now for each non root node say u, if its child say v has no path to the ancestor nodes of u (i.e parents of node u). Then node u is an articulation point.  
<figure>
<center><img src="https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/gfg-acp.png?raw=True" alt="drawing" width="400"/></center>
</figure>

**Implementation of Second Approach**:

<figure>
<center><img src="https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/gfg1.png?raw=True" alt="drawing" width="400"/></center>
</figure>


1. The key idea is two maintain two things for each `u` vertex: Its discovery time `disc` (the time we traverse that node) and `low` discovery time of a node which is reachable from `u` and is the least.
2. Remember that leaf nodes can never be cut vertex
3. For each non root node if its `disc[u] <= low[u]` then u is a cut vertex or articulation point.
4. **DFS**:
5. We also maintain another vector namely `parent` which maintains the parent of current node. This is to check in dfs if my child `v` is my parent then we dont consider it to update `low[u]`.
6. We can start with any source node say `u`. We also maintain visited array.
7. We apply dfs in the following way
8. Intialize static time = 0
9. Set both `disc[u] and low[u]  to ++time`
10. Set visited[u] = true
11. Now for each child `v` of `u` :
12. if `v` not visited then set `par[v]=u` and call dfs on `v`.
13. We set `low[u] = min(low[u] , low[v])`   // This means that the lowest discovery is either u itself or the least one reachable by its child.
14. if `v` was visited and and `parent[u]!=v` then also set `low[u] = min(low[u] , low[v])`  
15. Once we have done traversing all children of u
16. We see if u is a root node, if it is then if it had more than one unvisited child (during traversing just maintain count) then its an articulation point.
17. If it is a non root and non leaf node and  `disc[u] == low[u]` then `u` is an articulation point.

```
void dfs(vector<vector<int>> &adjlist,int u, vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<int> &par, vector<int> &ans){
    
    static int time = 0;
    visited[u] = true;
    ++time;
    disc[u] = low[u] = time;
    int cnt = 0;
    for (int &x : adjlist[u]){
        if(!visited[x]){
            cnt++;  //Maintaining count of unvisited children for root node
            par[x] = u;
            dfs(adjlist, x, visited, disc, low, par, ans);
            low[u] = min(low[u], low[x]);
            
            // if(low[x] > disc[u]){                               //Code for bridge
            // cout<<" bridge : "<<u<<" "<<x<<endl;
        }
        else if(x!=par[u]){
            low[u] = min(low[u], low[x]); 
        }


    }
    if(disc[u] == 1 && cnt>1){  //For root node.
        ans.push_back(u);   
    }
    else if(disc[u]!=1 && adjlist[u].size()>1 && disc[u]<=low[u]){  

                ans.push_back(u);  //For non root non leaf node.
            }
    
}
class Solution {
public:
    vector<int> criticalConnections(int n, vector<vector<int>>& connections) {
        // create adjlist
        // DO dfs and note discovery and smallest node reachable
        vector<vector<int>> adjlist(n);
        for(int i=0; i<connections.size(); i++){
            add_edge(adjlist, connections[i][0], connections[i][1]);
        }
        vector<int> disc(n);
        vector<int> low(n);
        vector<bool> visited(n, false);
        vector<int> par(n,-1);
        int count = 0;
        vector<int> ans;
        for(int i=0; i<adjlist.size(); i++){
            if(!visited[i]){
                dfs(adjlist, i, visited, disc, low, par, ans);
            }
        } 
        return ans;
    }
};

```
---

#### 12 Finding Bridges in a graph
**Approach:**
1. Bridges are the set of cut edges in a graph
2. The idea is exactly the same as in the articulation points. We find discovery and lowest discovery reachable for each node. (low is used to represent if ancestors are reachable)
3. Now for an edge `(u,v)` if low[v] <= disc[u] then it is not a bridge   because ancestors are reachable from v.
4. The code is commented in the above code.

---

#### 13 Find Strongly Connected Components using Tarzan's.
**Approach:**
1. This is a very simple approach. Kojaru's algo took two parse of DFS but Tarzan takes only one.
2. We use the same concept of discovery and lowest reachable discovery as in Bridges and Articulation points.
3. We have a directed graph and we need to find the strongly connected componenets.
4. We need to rememeber the main concept that, after we have build up low and high for all nodes. After starting from leaf nodes whenever we find `low[u] = disc[u]` then it means all nodes beneath than node is a part of some strongly connected component.
5. We make a use of stack to keep all nodes while traversing and once all the child nodes are traversed for a node `u` we check this condition `low[u] = disc[u]`. And pop it.
6. We also make use of extra vector namely stack_member which keeps record of the nodes currently present in the stack.
7. stack_memeber if used to see if for a node `u` we traverse a child node which is visited and not a stack_member than that means it is a cross edge.
8. We dont update low when we see cross edge because it is not a back_edge.

```
void add_edge(vector<vector<int>> &adjlist, int u, int v){
	adjlist[u].push_back(v);
}


dfs(vector<vector<int>> &adjlist, int u, vector<int> &d, vector<int>&low, vector<bool> &visited, vector<bool> &stmemb, vector<vector<int>> &ans, stack<int> &st){

	static int time = 0;
	d[u] = low[u] = ++time;
	visited[u] = true;
	st.push(u);
	stmemb[u]=true;

	for(int &x : adjlist[u]){
		if(!visited[x]){
			dfs(adjlist, x, d, low, visited, stmemb, ans, st);
			low[u] = min(low[u],low[x]);
		}
		else if(stmemb[x]){
			low[u] = min(low[u], low[x]);
		}
	}

	if(low[u] == d[u]){
		vector<int> cand;
		while(!st.empty() && st.top()!= u){
			cand.push_back(st.top());
			stmemb[st.top()] = false;
			st.pop();
		}
		if(!st.empty() && st.top() == u){
			cand.push_back(st.top());
			stmemb[st.top()] = false;
			st.pop();
		}
		ans.push_back(cand);
	}

}
class Solution {
public:
    vector<vector<int>> SCC(int n, vector<vector<int>>& edges) {
        // create adjlist
        // DO dfs and note discovery and smallest node reachable
        vector<vector<int>> adjlist(n);
        for(int i=0; i<edges.size(); i++){
            add_edge(adjlist, edges[i][0], edges[i][1]);
        }
         
        vector<int> d(n);
        vector<int> low(n);
        vector<bool> visited(n,false);
        vector<bool> stmemb(n,false);
        stack<int> st;
        vector<std::vector<int>> ans;
        for(int i=0;i<adjlist.size();i++){
        	if(!visited[i]){
        		dfs(adjlist, i, d, low, visited, stmemb, ans, st);
        	}
        }
        return ans;
    }
};

```

---

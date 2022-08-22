#### [1a. Find Cycle in Directed Graph/ Course Schedule](https://leetcode.com/problems/course-schedule/)
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
#### [1b. Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
**Approach : Topological Sort**
1. Will be discussing topo using dfs as topo using bfs is already discussed below.
2. Now to create adjlist, we are given `prereq:[0,1]` meaning 1 is a prereq of 0 so I have an edge from 1 to 0 in my graph cuz before taking 0 we must take 1.
3. Now we make in_deg vector represent in_deg of each vertex
4. We also maintain done or visited. Also as there can be a cycle we maintain count of the nodes obtained in our ans.
5. We apply dfs on each vertex which has in_deg 0 and decrement its in_deg by 1.
6. Finally if the count matches the numCourses then it means there was no Cycle. return ans. Else return `{}`.

```
void dfs_toposort(int i,vector<vector<int>> &adjlist, int numCourses, vector<int> &in_coming, int &count, vector<int> &ans, vector<int> &done){
    
        done[i]++;
        count++;
        ans.push_back(i);
        for(int &j:adjlist[i]){
            in_coming[j]--;
            if(!in_coming[j] && !done[j]){
                dfs_toposort(j, adjlist, numCourses, in_coming, count, ans, done);
            }
        }
    
}

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prereq) {
        vector<vector<int>> adjlist(numCourses);
        for(int i=0; i<prereq.size(); i++){
            adjlist[prereq[i][1]].push_back(prereq[i][0]);
        }
        vector<int> done(numCourses,0);
        vector<int> in_coming(numCourses,0);
        for(int i=0; i<adjlist.size(); i++){
            for(int j=0; j<adjlist[i].size(); j++){
                in_coming[adjlist[i][j]]+=1;
            }
        }
        // return toposort_bfs(numCourses, adjlist);
        vector<int> ans;
        int count=0;
        for(int i=0; i<numCourses; i++){
        if(!done[i] && !in_coming[i]){
            dfs_toposort(i, adjlist, numCourses, in_coming, count, ans, done);
        }
    }
        if(count == numCourses) return ans;
        return {};
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
        // Priority queue represents : pair<int,int> where pair.first is the distance of vertex pair.second from the current vertex.
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
2. We maintain boolean final vector which represents if the vertex is completed or not so that vertex doesnt repeat as we are pushing multiple copies of the vertex.

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
        priority_queue<pair<int,int>, vector<pair<int,int>> , Solution::compare> pq; // We can use greater<pair<int,int>> here instead of compare class but greater<>() always sort on first element so make sure first element of pair is the distance.
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

#### [12 Finding Bridges in a graph](https://leetcode.com/problems/critical-connections-in-a-network/submissions/)
**Approach:**
1. Bridges are the set of cut edges in a graph
2. The idea is exactly the same as in the articulation points. We find discovery and lowest discovery reachable for each node. (low is used to represent if ancestors are reachable)
3. Now for an edge `(u,v)` if low[v] <= disc[u] then it is not a bridge   because ancestors are reachable from v.
```

void add_edge(vector<vector<int>> & adjlist, int u, int v){
    adjlist[u].push_back(v);
    adjlist[v].push_back(u);
}
void dfs(vector<vector<int>> &adjlist, vector<bool> &visited, vector<int> &disc, vector<int> &low, int i, vector<vector<int>> & ans, vector<int> &par){
    static int time = 0;
    low[i] = disc[i] = ++time;
    visited[i] = true;
    for(int &x : adjlist[i]){
        if(!visited[x]){
            par[x] = i; 
            dfs(adjlist, visited, disc, low, x, ans, par);
            
            low[i] = min(low[i], low[x]);
            if(low[x]>disc[i]){
                ans.push_back({i,x});
            }
        }
        else{
            if(x!=par[i]){
                low[i] = min(low[i], low[x]);
            }
        }
    }
    
}
class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // create adjlist
        // DO dfs and note discovery and smallest node reachable
        vector<vector<int>> adjlist(n);
        for(int i=0;i<connections.size();i++){
            add_edge(adjlist, connections[i][0], connections[i][1]);
        }
        vector<int> disc(n);
        vector<int> low(n);
        vector<bool> visited(n, false);
        vector<vector<int>> ans;
        vector<int> par(n, -1);
        for(int i=0; i<adjlist.size(); i++){
            if(!visited[i]){
                dfs(adjlist, visited, disc, low, i, ans, par);    
            }
        }
        return ans;
    }
};
```

---

#### 13 Find Strongly Connected Components using Tarjan's.
**Approach:**

<figure>
<center><img src="https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/tarzanalgo.png?raw=True" alt="drawing" width="400"/></center>
</figure>

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

#### [14. Kruskal using  Union and Find](codingninjas.com/codestudio/problems/1082553?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=0)

**Approach**
1. You can find implementation of Union and find in `Disjoint_Set.md` file.
2. Algo is really simple. Sort the edges based on their weights.
3. Now traversing sorted edges in increasing order. 
4. We check if the vertices of an edge lie in same set, if it does then we cant put an edge between them as it will lead  to a cycle.
5. if find(u)!=find(v) then we Union(u,v) and result+=(w(u,v))

```
int kruskalMST(int n, int m, vector<vector<int>> &graph) {
	// Write your code here.
    
    sort(graph.begin(), graph.end(), compare);
    // Kruskal take edges in increasing order of weight and add it in the graph until we have n-1 edges. We dont add in case of cycles.
    int result = 0;
    vector<int> parent(n);
    for(int i=0; i<parent.size(); i++) parent[i] = i;
    vector<int> rank(n, 0);
    for(int i=0, s=0; i< graph.size() && s<n-1; i++){
        int u = graph[i][0] - 1, v = graph[i][1] - 1;
        if(find(u, rank, parent)!=find(v, rank, parent)){
            Union(u, v, rank, parent);
            s++;
            result += (graph[i][2]);
        }
        
    }
    return result;
    
}
```
---

#### [15. Clone a graph](https://leetcode.com/problems/clone-graph/submissions/)
**Approach:DFS Efficient**
1. The efficient approach is to maintain an unordered_map of old nodes to the corresponding new nodes.
2. Apply dfs on the intial node, check its neighbors
3. if the neighbor node already created or exist in mp then just add an edge in the new nodes from node to neighbour.
4. else create a copy of the neighbour node, add an edge to this neighbour node, add it  in map and call dfs on it recursively.

```
void dfs_cloneg(Node *node, unordered_map<Node*, Node*> &mp){
    
    
    for(int i = 0; i<node->neighbors.size(); i++){
        if(mp.find(node->neighbors[i])==mp.end()){
            Node *cl = new Node(node->neighbors[i]->val);
            mp[node->neighbors[i]] = cl;
            mp[node]->neighbors.push_back(cl);
            dfs_cloneg(node->neighbors[i], mp);
        }
        else{
            mp[node] -> neighbors.push_back(mp[node->neighbors[i]]);
        }
        
    }
    
    
    
}

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(node == NULL) return NULL;
        
        unordered_map<Node*, Node*> mp;
        
        
        Node *root = new Node(node->val);
        
        mp[node] = root;
        dfs_cloneg(node, mp);
        return root;
}
```

**Approach: BFS**
1. This is another less efficient approach
2. In this, we start applying bfs on the root node after creating a copy of it and we push them together in the queue (This is the crux that we must put both node and its copy together into the dict.).
3. Now we go through its neighbors, we also maintain visited array and nodes array which represents what all nodes are already created.
4. Now if the neighbor is already visited then nothing to do
5. else if the neighbor's copy has already been created then set neighbors to that else create a copy and push both the node and its copy to queue.

---

#### [16. Word Ladder](https://leetcode.com/problems/word-ladder/)
Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.  
**Approach - Simple : `TC: (O(n^2*m) + O(n^2*m))` (m is the wordlen and n is the wordlist length)**
1. Check if the begin word and end word exists in the wordlist and note their indices as src and tgt.
2. if beginword doesnt exist then add it to the word list, if endword doesnot exist then return 0
3. Now create adjlist in `O(n^2*m)` checking all the strings for a particular string and matching them and adding them to their neighbors. (Undirected graph)
4. Now simply apply bfs to get the dist for the tgt node.

**Approach - Smart : `TC: (O(n^2*m) + O(m^2*n))`**
1. In this we dont create an adjlist but an unordered_map which maps a particular pattern to a vector of indices of wordlist.
2. for each word in wordlist we mask one char and generate a pattern and add its idx to the corresponding key pattern in map.
3. This ensures that for a pattern all the corresponding indices differ in atmost 1 char
4. Now we apply bfs, during find the neighbors of a specific node we again mask its chars one by one and find all the corresponding neighbors. 

```
int bfs_smart(int src, int tgt, unordered_map<string, vector<int>> &mp, vector<string> &wordList){
    queue<int> q;
    vector<int> visited(wordList.size(),0);
    vector<int> dist(wordList.size(),INT_MAX);
    dist[src]=1;
    
    q.push(src);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        visited[x]=1;
        string src_str = wordList[x];
        for(int j = 0; j<src_str.length(); j++){
            string temp = src_str;
            temp[j]='*';
            for(int k = 0; k<mp[temp].size(); k++){
                int tar = mp[temp][k];
                // cout<<" tar = "<<tar<<endl;
                if(tar!=x){
                    if(!visited[tar]){
                        if(dist[tar] > dist[x]+1){
                            
                            dist[tar] = dist[x]+1;
                            // cout<<wordList[tar]<<" = "<<dist[tar]<<endl;
                            q.push(tar);
                        }

                    }
                }
            }
        }
        
    }
    return dist[tgt] == INT_MAX? 0: dist[tgt];
    
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // The trick is how you create the adjacency list either in O(n^2*m) or O(n*m^2) where n is len(wordList) and m is len(wordList[i]), The rest is similar
        int flag=-1, tgt=-1;
        for(int i=0; i<wordList.size();i++){
            if(wordList[i] == beginWord){
                flag=i;
            }
            if(wordList[i] == endWord){
                tgt = i;
            }
        }
        if(tgt == -1){
            return 0;
        }
        if(flag==-1){
            wordList.push_back(beginWord);
            flag = wordList.size()-1;
        }
        // For smart approach we find all the possible matching patterns of a string and push that in a mp
        
        unordered_map<string,vector<int>> mp;
        for(int i=0; i<wordList.size(); i++){
            
            for(int j=0; j<wordList[i].length(); j++){
                string x = wordList[i];
                x[j] = '*';
                mp[x].push_back(i);
            }
        }
        return bfs_smart(flag, tgt, mp, wordList);
    }
```

---

#### [17. Pacific Atlantic Ocean : Hard for me](https://leetcode.com/problems/pacific-atlantic-water-flow/)
**Approach : O(n^2*m + n*m^2)**  
1: We apply dfs from all the boundaries checking what all cells are reachable from the boundary in the defined manner (order of heights)
2. We check for the boundaries of pacific and atlantic and maintain respective vectors.
3. finally we find intersection of these vectors as our ans.

```
bool finder(vector<vector<int>> &visit, vector<int> &s){
    for(int i=0; i<visit.size(); i++) {
        if(visit[i][0] == s[0] && visit[i][1] == s[1]) return true;
    }
    return false;
}
void traverse(int i, int j, vector<vector<int>> &visit, vector<vector<int>> &heights, int prevheight, int m,int n){
    vector<int> s = {i,j};
    if(finder(visit,s) || i<0 || j<0 || i>=m || j>=n || heights[i][j] < prevheight) return;
    
    visit.push_back({i,j});
    // mp[{i,j}]=1;
    traverse(i+1, j, visit, heights, heights[i][j], m, n);
    traverse(i-1, j, visit, heights, heights[i][j], m, n);
    traverse(i, j+1, visit, heights, heights[i][j], m, n);
    traverse(i, j-1, visit, heights, heights[i][j], m, n);
    
}

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> ans;
        int m = heights.size();
        int n = heights[0].size();
        vector<vector<int>> pac;
        vector<vector<int>> atl;
        for(int j=0; j<n; j++){
              traverse(0, j, pac, heights, heights[0][j],m,n);
              traverse(m-1, j,  atl, heights, heights[m-1][j],m,n);   
         }
        for(int i=0; i<m; i++){
              traverse(i, 0, pac, heights, heights[i][0],m,n);
              traverse(i, n-1,  atl, heights, heights[i][n-1],m,n);   
         }
        for(int i=0; i<pac.size(); i++){
            if(finder(atl, pac[i])){
                ans.push_back(pac[i]);
            }
        }
        return ans;
    }
};
```
A slightly better code is to use bit masking with dfs  

```
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> visited;
    void dfs(vector<vector<int>>& matrix, int x, int y, int pre, int preval){
        if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size()  
                || matrix[x][y] < pre || (visited[x][y] & preval) == preval) 
            return;
        visited[x][y] |= preval;
        if (visited[x][y] == 3) res.push_back({x, y});
        dfs(matrix, x + 1, y, matrix[x][y], visited[x][y]); dfs(matrix, x - 1, y, matrix[x][y], visited[x][y]);
        dfs(matrix, x, y + 1, matrix[x][y], visited[x][y]); dfs(matrix, x, y - 1, matrix[x][y], visited[x][y]);
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        if (matrix.empty()) return res;
        int m = matrix.size(), n = matrix[0].size();
        visited.resize(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            dfs(matrix, i, 0, INT_MIN, 1);
            dfs(matrix, i, n - 1, INT_MIN, 2);
        }
        for (int i = 0; i < n; i++) {
            dfs(matrix, 0, i, INT_MIN, 1);
            dfs(matrix, m - 1, i, INT_MIN, 2);
        }
        return res;
    }
};
```


---

#### [18. Word Search](https://leetcode.com/problems/word-search/)  
Given an m x n grid of characters board and a string word, return true if word exists in the grid.  
**Approach**:  
1. Simple Brute Force, go through each direction and maintain the pos of the currently matched char.
2. Write separate calls for each direction instead using a direction vector, as the latter gives TLE.

```
bool dfs(int i, int j, string &word, vector<vector<char>> &board, int pos, int m, int n){
    
    if(pos == word.length()) return true;
    if(i<0 || i==m || j<0 || j==n || board[i][j]!=word[pos]){
        return false;
    }
    bool flag;
    char temp = board[i][j];
    board[i][j] = '*';
    flag = (dfs(i+1, j, word, board, pos+1, m,n) || dfs(i-1, j, word, board, pos+1, m,n) || dfs(i, j+1, word, board, pos+1, m,n) || dfs(i, j-1, word, board, pos+1, m,n)); //Always write separate calls like this.
    board[i][j] = temp;
     return flag;   
}

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        
        int m = board.size();
        int n = board[0].size();    
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                    if(dfs(i,j,word,board,0,m,n))
                        return true;   
            }
        }
        return false;
    }
};
```
`TC: O(m*n* 4^(len(target))), where tc of dfs is 4^(len(target))`


#### [19. Island Perimeter](https://leetcode.com/problems/island-perimeter/)  
Given an island surrounded by water, find its perimeter.  

**Approach:DFS**
1. Simple logic is that perimeter of each cell in island is equal to the no. of sides it is surrounded by water or final boundary i.e the neighbour cell should be ` i<0 || j<0 || i==m || j==n || grid[i][j] = 0`.
2. We sum up all the boundries for each cell and return
3. We also mark the visited cell so that we dont visit it again.

```
int dfs(int i, int j, vector<vector<int>> &grid, int m, int n){
    if(i<0 || j<0 || i>=m || j>=n || grid[i][j] == 0) return 1;
    if(grid[i][j] == -1) return 0;
    
    
    grid[i][j] = -1;
    
    return dfs(i+1, j, grid, m, n) + dfs(i-1,j,grid,m,n) + dfs(i,j+1,grid, m, n) + dfs(i, j-1, grid, m, n);
    
    
    
}

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++)
            {
                if(grid[i][j]){
                    return dfs(i, j, grid, m, n);
                }
            }
        }    
        return 0;
    }
};
```

`TC : O(m*n + 4^(size of island))`
---

#### [20. Reorder routes to make all paths lead to zero node]()

Given acyclic graph, we want all nodes to point to zero node i.e all nodes have one direction pointing to 0 and there is path from each node to node 0.  
Find min no of edges u need to change to do the same.  
**Approach**  
1. We will use BFS, we compute two adjlist, one which we currently have and another of the transpose of the graph.
2. We start by pushing node 0 to the queue. We also maintain visited array as we can be visiting a node twice even though there is no cycle but due to traversing both simple and transpose of the graph.
3. We pop queue top and mark it as visited.
4. Then we find its neighbours in the simple graph, these are the edges that should have been pointing towards zero hence we increase the count with number of neighbors and push them to queue.
5. Then we find its neighbours in the transpose of the graph, these are the neighbors that are valid i.e they are already pointing towards zero, we simply push them also into the queue.
6. Now we do the same thing for each node in queue.

```
class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<int>> alist1(n);
        vector<vector<int>> alist2(n);
        for(int i=0 ;i< connections.size(); i++){
                alist1[connections[i][0]].push_back(connections[i][1]);
                alist2[connections[i][1]].push_back(connections[i][0]);
            
        }
        int count=0;
        queue<int> q;
        q.push(0);
        vector<int> visited(n,0);
        while(!q.empty()){
            
            
            int x = q.front();
            q.pop();
            if(!visited[x]){
                visited[x] = 1;
                
                for(int &j : alist2[x]){
                    if(!visited[j]){
                        q.push(j);
                    }    
                }
                for(int &k : alist1[x]){
                    if(!visited[k]){
                        count++;
                        q.push(k);
                    }
                
    
                }
            }
        }
        return count;
    }
};
```

---

#### [21. Alien Dictionary - HARD](https://www.lintcode.com/problem/892/)
Given a list of latin words lexicographically sorted as per some other langauage rules. Find the order of words  


**Approach : Topological Sort Kahn's Algo**
1. Order can be found between adjancent words and finding the first nonmatching char, e.g `[xy,xz]` here we get to know that y is smaller than z. Hence there will be an edge from y to z.
2. Secondly if `[xyz,xy]` such order appears we need to return "". 
3. We apply toposort to find the order, there can be more than one components reponsible for multiple ans. (Just lexicographically join the multiple ans)
4. If after applying kahn's algo there are still some nodes with non zero inorder then that means there existed a cycle for which we return "".

```
string insert(char x, string final_ans){
    
    string ret = "";
    int flag=0;
    for(int i=0; i<final_ans.length(); i++){
        if(x<final_ans[i] && flag==0){
            flag=1;
            ret+=x;
        }
        else if(x == final_ans[i]) return final_ans;

        ret+=(final_ans[i]);
    }
    if(flag==0){
        ret+=(x);

    }
    return ret;

}

class Solution {
public:
    /**
     * @param words: a list of words
     * @return: a string which is correct order
     */
    string alienOrder(vector<string> &words) {
        // Write your code here
        // cout<<"started"<<endl;
        vector<int> exist(26,0);
        vector<vector<int>> adjlist(26);
        for(int i=0; i<words.size(); i++){
            exist[words[i][0]-'a'] =1;
            for(int j=1; j<words[i].size(); j++){
                exist[words[i][j]-'a']=1;
            }
            if(i!=0){
                int x=0;
                if(words[i-1]!=words[i])
                {
                    while(words[i-1][x] == words[i][x]) x++;
                    if(x==words[i].length()) return "";
                    if(x<words[i-1].length()){
                        adjlist[words[i-1][x]-'a'].push_back(words[i][x]-'a');
                    }
                }
            }

        }
        vector<int> in_order(26,0);
        for(int i=0; i<adjlist.size(); i++){
            for(int j=0; j< adjlist[i].size(); j++){
                in_order[adjlist[i][j]]++;
            }
        }
        string ans="";
        int count=0;
        queue<int> q;
        vector<int> start;
        vector<string> an;
        for(int i=0; i<in_order.size(); i++){
            if(exist[i] && in_order[i]==0)
                start.push_back(i);
            }
        
        // cout<<"first element done"<<endl;
        for(int m=0; m<start.size(); m++){
            ans = "";
            q.push(start[m]);
            while(!q.empty()){
            int x = q.front();
            q.pop();
            char c = 'a' + x;
            ans+=c;
            for(int &j : adjlist[x]){
                c = 'a' + j;    
                in_order[j]--;
                if(in_order[j]==0){
                    q.push(j);
                }
            }
            
        }
        an.push_back(ans);

        }
        for(int &m:in_order) if(m!=0) return "";
        
        string final_ans = an[0];
        for(int x=1; x<an.size();x++) {
            for(int i=0; i<an[x].length(); i++){
                final_ans = insert(an[x][i], final_ans);
            }
        }
        return final_ans;
    }
};
```

---

#### [22. Min Cost to connect all points](https://leetcode.com/problems/min-cost-to-connect-all-points/)
Conventional Kruskal and Prims gives TLE.  

**Approach: MST using Kruskal with min heap instead of sorting (saves space and memory)**

```
int mst_Kruskal(vector<vector<int>>& points){
        int md=0;
        int n = points.size();
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        for(int i=0; i<points.size()-1; i++){
            for(int j=i+1; j<points.size(); j++){
                md = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                pq.push({md, i, j});
            }
        }
        
        // sort(edges.begin(), edges.end(), comparator );
        
        // Need to make functions UNION and Find for KrushKal
        vector<int> parents(n,0);
        for(int i = 0; i< parents.size(); i++){
            parents[i] = i;
        }
        vector<int> rank(n,1);
        int ans=0;
        int u,v,pu,pv;
        int count=n-1; // Total no of edges required where n is no of vertices
        while(count>0){
            vector<int> x = pq.top();
            pq.pop();
            u = x[1];
            v = x[2];
            pu = find(u, parents);
            pv = find(v, parents);
            if(pu != pv){
                unions(pu,pv,parents,rank);
                ans+=x[0];
                count--;
            }
            }
    return ans;
}
```

**Approach: Prims more efficient**  
Instead of precomputing adjlist, we find all the edge weights on the fly  
We start with vertex 0, push it into priority queue pq.  
Then we find weight of this vertex with all corresponding vertices and push them to pq.  
Then we get pq.top and do the same thing again.


```
int mst_prims(vector<vector<int>> &points){
    vector<vector<vector<int>>> adjlist(points.size());
        int md=0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        
        vector<int> visited(points.size(),0);
        
        int ans=0;
        pq.push({0,0});
        int count=points.size();
        while(!pq.empty() && count>0){
            
            pair<int,int> p = pq.top();
            pq.pop();
            if(!visited[p.second]){
                
                visited[p.second] =1 ;
                ans+=(p.first);  
                count--;
                for(int j=0; j<points.size(); j++){
                    if(p.second!=j){
                        if(!visited[j]){
                            pq.push({abs(points[p.second][0] - points[j][0])+abs(points[p.second][1] - points[j][1]),j});
                        }
                    }
                }
                
            }
            
            
        }
        return ans;
}
```  

**Another Implementation of Kruskal using make_heap (takes 500ms lesser than previous kruskal )**  
If we do not need to push the nodes into the heap again and again then we can just use make_heap which takes o(n) time to build then keep on popping nodes till its empty.  

```
int mst_Kruskal_heap(vector<vector<int>>& points){
        int md=0;
        int n = points.size();
        // priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        vector<vector<int>> hp;
        for(int i=0; i<points.size()-1; i++){
            for(int j=i+1; j<points.size(); j++){
                md = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                hp.push_back({md, i, j});
            }
        }
        make_heap(hp.begin(),hp.end(), greater<vector<int>>());
        
        // Need to make functions UNION and Find for KrushKal
        vector<int> parents(n,0);
        for(int i = 0; i< parents.size(); i++){
            parents[i] = i;
        }
        vector<int> rank(n,1);
        int ans=0;
        int u,v,pu,pv;
        int count=n-1;
        while(count>0){
            pop_heap(hp.begin(), hp.end(), greater<vector<int>>());
            vector<int> x = hp.back();
            hp.pop_back();
            u = x[1];
            v = x[2];
            pu = find(u, parents);
            pv = find(v, parents);
            if(pu != pv){
                unions(pu,pv,parents,rank);
                ans+=x[0];
                count--;
            }
            }
    return ans;
}
```

---

#### [23, Swim in Rising Water](https://leetcode.com/problems/swim-in-rising-water/)
**Approach : Brute Force DFS: 4^(n^2)**  
1. Can use memoziation here as the function calls are not unique: if we set `dp[i][j]` to something then its possible that a better value exist through some other path.

```

int swim(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp, int m, int n){
    //base case
    if(i<0 || j<0 || i>=m || j>=n || grid[i][j] == -1) return INT_MAX;
    if(i==m-1 && j==n-1) return grid[i][j];
    int temp = grid[i][j];
    grid[i][j] = -1;
    int a = swim(i+1,j,grid,dp,m,n);
    int b = swim(i-1,j,grid,dp,m,n);
    int c = swim(i,j+1,grid,dp,m,n);
    int d = swim(i,j-1,grid,dp,m,n);
    grid[i][j] = temp;
    
    return max(grid[i][j],min(min(a,b),min(d,c)));
    
}
```



**Approach: Modified Dijkstra : O(n^2 logn)**
1. Key idea is to keep the max value as the dist in any given path say in path src to v, the `dist[v]` is the max value seen in that path
2. Now say there is another path from src to x, `dist[x]` and both x and v has tgt as neighbour so we would want to follow min `dist[x]` and `dist[v]` to follow.
3. This is done using priority queue. 
4. We are ulimately finding the min of max in all paths from src to tgt. Hence we use dijkstra

```
class compared{
    public:
  bool operator() (const vector<int> &a, const vector<int> &b){
      return a[0]>b[0];
  }  
};
int dij_swim(vector<vector<int>> &grid, vector<vector<int>> &visited){
    priority_queue<vector<int>, vector<vector<int>>, compared> pq;
    pq.push({grid[0][0],0,0});  
    int ans = INT_MIN;
    vector<vector<int>> dist(grid.size(), vector<int>(grid[0].size(), INT_MIN));
    dist[0][0] = grid[0][0];
    while(!pq.empty()){
        vector<int> p = pq.top();
        pq.pop();
        int u = p[0];
        int i=  p[1];
        int j=  p[2];
        if(!visited[i][j]){
            visited[i][j] = 1;
            if(i+1<grid.size()){
                if(!visited[i+1][j]){
                    dist[i+1][j] = max(u, grid[i+1][j]);
                    pq.push({dist[i+1][j], i+1, j});    
                }
                

            }
            if(i-1>=0){
                if(!visited[i-1][j])
                {
                    dist[i-1][j] = max(u, grid[i-1][j]);
                    pq.push({dist[i-1][j], i-1, j});    
                }
            }
            if(j+1<grid[0].size()){
                if(!visited[i][j+1])
                {
                    dist[i][j+1] = max(u, grid[i][j+1]);
                    pq.push({dist[i][j+1], i, j+1});    
                }
            }
            if(j-1>=0){
                if(!visited[i][j-1])
                {
                    dist[i][j-1] = max(u, grid[i][j-1]);
                    pq.push({dist[i][j-1], i, j-1});    
                }
            }

        }
    }
    return dist[grid.size()-1][grid[0].size()-1];
    
}
```

---


#### [24. Surrounded Regions](https://leetcode.com/problems/surrounded-regions/)
Given an m x n matrix board containing 'X' and 'O', capture all regions that are 4-directionally surrounded by 'X'. A region is captured by flipping all 'O's into 'X's in that surrounded region.  
**Approach : DFS**  
1. We do reverse engineering here i.e instead of find surrounded components and flipping them, we instead find all the non surrounded elements and mark them and then finally we flip the rest "O" and unmark the previously marked components.
2. For each "O" element in the grid border apply DFS and mark them temporarily.
3. Then finally flip the remaining "O" and unmark the temp components.

```
void flip(int i, int j, vector<vector<char>> &board){
    
    if(i<0 || i>=board.size() || j<0  || j>=board[0].size() || board[i][j] == 'X' || board[i][j] == '-') return;
    
    board[i][j] = '-';
    flip(i+1,j,board);
    flip(i-1,j,board);
    flip(i,j+1,board);
    flip(i,j-1,board);
    return;
}

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        
        for(int i=0; i<board.size(); i++){
            if(board[i][0] == 'O') flip(i,0,board);
            if(board[i][board[0].size()-1] == 'O') flip(i,board[0].size()-1,board);
            
        }
        
        for(int j=0; j<board[0].size(); j++){
            if(board[0][j] == 'O') flip(0,j,board);
            if(board[board.size()-1][j]=='O') flip(board.size()-1,j,board); 
        }
        for(int i=0;i<board.size() ;i++){
            for(int j=0; j<board[0].size(); j++){
                if(board[i][j] == 'O') board[i][j] = 'X';
                if(board[i][j] == '-') board[i][j] = 'O';
            }
        }
        
        return;
    }
};
```
`TC: O((m+n)*(m*n))`
---

#### [25. Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/)
**Bellman Ford with K+1 relaxes**  
1. The implementation of Bellmand ford is not conventional. This is the proper implementation as the actual algo.
2. At each step i  we have a smallest dist d from the src with atmost i-1 steps.

```
 int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> dist(n, 1e8);
        dist[src] = 0;
        vector<int> dg(n, 1e8);
        for(int i=0; i<=k; i++){     
            for(int j=0; j<flights.size(); j++){
                if(dg[flights[j][1]] > dist[flights[j][0]] + flights[j][2]){
                dg[flights[j][1]] = dist[flights[j][0]] + flights[j][2];       
                }
                
            }
            dist = dg;

        }
        if(dist[dst] >= 1e8) return -1;
        return dist[dst];
    }
```
---

#### [26. Most Stones Removed with Same Row or Column VV.IMP Google](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/)
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

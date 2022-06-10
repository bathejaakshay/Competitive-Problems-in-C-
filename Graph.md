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

#### [3. Topological Sort using BFS](https://practice.geeksforgeeks.org/problems/topological-sort/1)
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

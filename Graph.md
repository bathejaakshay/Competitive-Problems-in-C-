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

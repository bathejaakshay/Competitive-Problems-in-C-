## TRIE

1. Trie is an efficient information retrieval data structure.  
2. Using Trie, search complexities can be brought to optimal limit (key length).  
3. If we store keys in a binary search tree, a well balanced BST will need time proportional to M * log N, where M is the maximum string length and N is the number of keys in the tree. Using Trie, we can search the key in O(M) time.
4. However, the penalty is on Trie storage requirements.
5. Tries is a tree that stores strings. 
6. The maximum number of children of a node is equal to the size of the alphabet.
7. Trie supports search, insert and delete operations in O(L) time where L is the length of the key.

**Advantages over other DS**

1. With Trie, we can insert and find strings in O(L) time where L represent the length of a single word. This is obviously faster than BST. This is also faster than Hashing because of the ways it is implemented. We do not need to compute any hash function. No collision handling is required (like we do in open addressing and separate chaining)
2. Another advantage of Trie is, we can easily print all words in alphabetical order which is not easily possible with hashing.
3. We can efficiently do prefix search (or auto-complete) with Trie.

#### Functionalities

1. It generally provides 3 functionalities: insert, search and startswith.
2. The structure of a Trie Node contains two things, namely, Trie Pointer array of size 26 to refer to its children alphabets, and is_end keyword which represents that the word of which I am a record of Ends here.
```
E.g say there is a word ab
then root has a reference to -> char a, char a has reference to char b record which has a keyword is_end=true;


Struture of a Trie Node

class Node{
  Node *ch[26]; // NULL by default;
  bool is_end=false; // Represents if the record ends here
  put_word(char c, Node *n) // set the ch[c-'a'] to empty node "n".
  Node * get_word(char c) // return ch[c-'a'] , returns the address of the record of c in current node.
}

```

---

#### [Implementing Trie DS](https://www.codingninjas.com/codestudio/problems/implement-trie_631356?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_tries_videos&leftPanelTab=0)

```
/*
    Your Trie object will be instantiated and called as such:
    Trie* obj = new Trie();
    obj->insert(word);
    bool check2 = obj->search(word);
    bool check3 = obj->startsWith(prefix);
 */

class Node{
    
    public:
        Node *ch[26]; //Automatically initialized with NULL
        bool is_end=false;
        bool isKey(char c){
            return ch[c-'a'];
        }
        void putChar(char c, Node *n){
            ch[c-'a'] = n;
        }
        Node *getChar(char c){
            return ch[c-'a'];
        }
        void ended(){
            is_end = true;
        }
};

class Trie {
private:
    Node *root = NULL; // To maintain the root for the current object
    
public:

    /** Initialize your data structure here. */
    Trie() {
        root = new Node();
        
    }

    /** Inserts a word into the trie. */
    // Insertion takes O(len(word)) time
    void insert(string word) {
        Node *node = root;
        for(int i=0; i<word.length(); i++){
            if(!node->isKey(word[i])){
                Node *ch_new = new Node(); //creating an empty Trie node where the char present at root will point to. This node will actually store all the information about the word[i] char, like all the words that come after this char or if any word ends at this char.
                node->putChar(word[i], ch_new);
            }
            node = node->getChar(word[i]);
        }
        node->ended(); // To mark an end to the current word
    }

    /** Returns if the word is in the trie. */
   // Search takes TC:O(len(word)).
    bool search(string word) {
        Node *node = root;
        for(int i=0; i<word.length(); i++){
           if(node->isKey(word[i])){
                   node = node->getChar(word[i]);
               }
           else{
                return false;
                }   
            }
        // If after iterating over the whole word, if the trie also reaches end then only that word exists.
            return node->is_end;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    //Starts with takes TC:O(len(prefix)) 
    bool startsWith(string prefix) {
        Node *node = root;
        for(int i=0; i<prefix.length(); i++){
            if(node -> isKey(prefix[i])){
                node = node->getChar(prefix[i]);   
            }
            else{
                return false;
            }
               
        }
        // if after iterating over the whole prefix, if it didnt fail anywhere then that means words with prefix "prefix" exists no matter it ends at prefix. So we return true;
         return true;
    }
};
```

---
#### [2. Implement Trie II](https://www.codingninjas.com/codestudio/problems/implement-trie_1387095?leftPanelTab=0)
Same as previous, just need to add few more functionalities
1. countWordsEqualTo(word)
2. countStartsWith(word)

**Approach**
1. The Trie node structure will change.
2. We need to maintain the count of pref `prefix_count` instead of just bool prefix.
3. We need to maintain the count of strings ended at a particular char `count_ended` instead of just bool ended
4. For erase we decrement these counts and count =0 means such pref or word is not there.

```
class Node{
    public:
     Node *ch[26];
     int end_count=0; //No. of strings that ends here
     int pref_count=0; //Count of strings with current prefix
     bool isKey(char c){
          return ch[c-'a'];
      }
      void putChar(char c, Node *nn){
          ch[c-'a'] = nn;
      }
      Node *getChar(char c){
          return ch[c-'a'];
      }
      void inc_pref(){
          pref_count++;
      }
      void ended(){
          end_count++;
      }
      int get_endcount(){
          return end_count;
      }
      int get_prefcount(){
          return pref_count;
      }
      void dec_prefcount(){
          pref_count--;
      }
      void dec_endcount(){
          end_count--;
      }
          
          
  
};
class Trie{
    private:
    Node *root;
    public:

    Trie(){
        // Write your code here.
        root = new Node();
    }

    void insert(string &word){
        Node *node = root;
        // Write your code here.
        for(int i=0; i<word.size(); i++){
            if(!node->isKey(word[i])){
                Node *nn_new = new Node(); // New node with current char
                node->putChar(word[i], nn_new);    
            }
            node = node->getChar(word[i]);
            node->inc_pref();
        }
        node->ended();
        
    }

    int countWordsEqualTo(string &word){
        // Write your code here.
        Node *node = root;
        for(int i=0; i<word.length(); i++){
            if(node->isKey(word[i])){
                node = node->getChar(word[i]);
            }
            else{
                return 0;
            }
        }
        return node->get_endcount();
    }

    int countWordsStartingWith(string &word){
        // Write your code here.
        Node *node = root;
        for(int i=0; i<word.length(); i++){
            if(node->isKey(word[i])){
                node = node->getChar(word[i]);
            }
            else{
                return 0;
            }
        }
        return node->get_prefcount();
    }

    void erase(string &word){
        // Write your code here.
        Node *node = root;
        for(int i=0; i<word.length(); i++){
            node = node->getChar(word[i]);
            node->dec_prefcount();
            
        }
        node->dec_endcount();
        
    }
};

```

---

#### [3. Word Search II : Trie + DFS](https://leetcode.com/problems/word-search-ii/submissions/)
**Approach : Only DFS**:  
1. This is similar to wordSearch I in which we were given only one word and we need to find if we can create that word from the grid or not.
2. But now we are given a list of words, we need to see what all words are possible outta these given words using the 2d grid.
3. For each cell using DFS algo same as Word Search 1 would given `TC: len(list of words) * M*N * 4^(M*N)`

**Approach: Using Trie and DFS**  
1. We create a Trie DS for all the given words W.
2. Now we dont need to check separately for each word in W, instead we can parallelly check for all the words possible at current index (i,j) in the grid using the DFS.
3. For each cell we start with the root of Trie, if there exist a word at root with value of the current cell then we append it in our current string, if is_end var is true, it means string collected till now is a legit word and hence we append it to the answer.
4. Else we go in all 4 directions and check for the respective words at next level of Trie.

```
class Node{
    public:
  Node *ch[26];
  bool is_end=false;
};

class Trie{
public:
    Node *root = new Node();
    void add_word(string w){
        Node *ptr = root;
        for(int i=0; i<w.length(); i++){
            if(ptr->ch[w[i]-'a'] == NULL){
                Node *nn = new Node();
                ptr->ch[w[i]-'a'] = nn;
            }
            ptr = ptr->ch[w[i]-'a'];
        }
        ptr->is_end=true;
    }
};

void dfs(int i, int j, string s,vector<vector<char>> &board, Node *root, vector<string> &ans, unordered_map<string,int> &mp){
    //base
    if(i<0 || j<0 || i>=board.size() || j>= board[0].size() || board[i][j] == '*'){
        return;
    }
    Node *n = root->ch[board[i][j]-'a']; 
    if(n){
        char temp = board[i][j];
        board[i][j] = '*';
        
        if(n->is_end){
            if(mp.find(s+temp)==mp.end()){
                mp[s+temp]=1;
                ans.push_back(s+temp);
            }
                
        }
        
        dfs(i+1,j, s+temp,board,n, ans, mp);
        dfs(i-1, j,s+temp,board,n, ans, mp);
        dfs(i,j+1, s+temp,board,n, ans, mp);
        dfs(i, j-1,s+temp,board,n, ans, mp);
        board[i][j] = temp;
        
    }
    
}

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie *t = new Trie();
        
        for(int i=0; i<words.size(); i++){
            t->add_word(words[i]);
        }
        vector<string> ans;
        string s="";
        unordered_map<string, int> mp;
        for(int i=0; i<board.size(); i++)
            for(int j=0; j<board[0].size(); j++){
                dfs(i,j,s,board,t->root,ans,mp);
            }
        
        
        return ans;
    }
};
```

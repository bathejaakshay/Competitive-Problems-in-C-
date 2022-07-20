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

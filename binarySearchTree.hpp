#ifndef __BST__
#define __BST__

#include <vector>

struct Node {
    Node* left;
    Node* right;
    int val;

    Node(int val1) : val(val1) {}
};

class BinarySearchTree {
    private:
        Node* insertHelper(Node* node , int val);                       
        void inorderHelper(Node* node);                                 
        void preorderHelper(Node* node);                                
        void postorderHelper(Node* node);                               
        Node* removeHelper(Node* node , int val);                       
        Node* searchHelper(Node* node, int val);                        
        Node* find_minHelper(Node* node);                               
        Node* find_maxHelper(Node* node);                                          
        int sizeHelper(Node* node);                                    
        int heightHelper(Node* node);                                   
        void clearHelper(Node* &node);                                  
        void serializeHelper(Node* node , std::vector<int>& vec);    
        void levelorderHelper(Node* node, int level);                     
        Node* successorHelper(Node* node, Node* &succ , int val);       
        Node* predecessorHelper(Node* node, Node* &pred , int val);     
        Node* copyHelper(Node* node);                                   
        bool is_validHelper(Node* node);                                
    
    public:
        BinarySearchTree();
        ~BinarySearchTree();
        void insert(int val);
        void remove(int val);
        void inorder();
        void postorder();
        void preorder();
        bool search(int val);
        int findMax();
        int findMin();
        int size();
        int height();
        void clear();
        std::vector<int> serialize();                                   
        void range_query(int start, int end);                           
        void levelorder();                                             
        void print_tree();                                              
        int successor(int val);                                         
        int predecessor(int val);                                       
        void update(int val , int new_val);                             
        Node* copy();                                                   
        int kth_smallest(int k);                                        
        int kth_largest(int k);                                         
        bool is_valid();                                                
        Node* find(int val);
        void setRoot(Node* node);
    private:
        Node* root;
};

#endif // __BST__

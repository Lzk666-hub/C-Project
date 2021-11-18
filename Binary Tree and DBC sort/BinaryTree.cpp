#include "BinaryTree.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* ================================== Node =================================== */

//REQUIRES:val is not empty
//MODIFIES:this
//EFFECTS:constructor
Node::Node(const int &val, Node *left, Node *right) :
    val(val), left(left) ,right(right){}


//EFFECTS:return the value of the node
int Node::getVal() const {
    return this->val;
}


//MODIFIES:this
//EFFECTS:set the value of the node with {newVal}
void Node::setVal(const int &newVal) {
    this->val=newVal;
}



//EFFECTS:return the pointer to the left child
Node * Node::getLeft() const {
    return this->left;
}


//EFFECTS:return the pointer to the right child
Node * Node::getRight() const {
    return this->right;
}



//MODIFIES:this
//EFFECTS: Set the left child of this node
// If the left child is null, creat a new node with {newVal}
// If the left child is not null pointer, update the value with {newVal}
void Node::setLeft(const int &newVal) {
    if(!left) left=new Node(newVal);
    else{
        left->setVal(newVal);
    }
}



//MODIFIES:this
//EFFECTS:Set the right child of this node
//        If the right child is null, creat a new node with {newVal}
//        If the right child is not null pointer, update the value with {newVal}
void Node::setRight(const int &newVal) {
    if(!right) right=new Node(newVal);
    else{
        right->setVal(newVal);
    }
}
/* =============================== Binary Tree =============================== */

//MODIFIES:this
//EFFECTS:constructor
BinaryTree::BinaryTree(Node *node) : root(node){}




//MODIFIES:this
//EFFECTS:constructor
BinaryTree::BinaryTree(const int &rootValue) {
    root=new Node(rootValue);
}




//MODIFIES:old
//EFFECTS:deep copy from node to old
void constructorHelper(Node* old,Node* node) {
    if (old->getLeft()){
        node->setLeft((old->getLeft())->getVal());
        constructorHelper(old->getLeft(), node->getLeft());
    }
    if (old->getRight()){
        node->setRight((old->getRight())->getVal());
        constructorHelper(old->getRight(), node->getRight());
    }
}


//MODIFIES:this
//EFFECTS:deep copy constructor
BinaryTree::BinaryTree(const BinaryTree &tree) {
    root = new Node((tree.root)->getVal());
    constructorHelper(tree.root, root);
}


//MODIFIES:this
//EFFECTS: Construct a binary tree with a list of values
BinaryTree::BinaryTree(std::vector<nodeValue> &source) {
    root= createFromVariant(source,0);
}

//MODIFIES:root
//EFFECTS:destructor helper function to delete all child node of a node
void destructorHelper(Node* root) {
    if (!root)return;
    destructorHelper(root->getLeft());
    destructorHelper(root->getRight());
    delete root;
}

//MODIFIES:this
//EFFECTS:destructor
BinaryTree::~BinaryTree() {
    destructorHelper(root);
}



//EFFECTS:Return true if the root node is null pointer
bool BinaryTree::empty() const {
    if(root== nullptr){
        return true;
    } else return false;
}



//EFFECTS:helper function to find the node with value {key}
Node * findHelper(Node *node, const int &key){
    Node *goal;
    if(node== nullptr) return nullptr;
    if(node->getVal()==key) return node;
    goal= findHelper(node->getLeft(),key);
    if(goal!= nullptr) return goal;
    goal= findHelper(node->getRight(),key);
    if(goal!= nullptr) return goal;
    else return nullptr;
}


//EFFECTS:find the node with value {key}
Node * BinaryTree::find(const int &key) const {
    return findHelper(this->root,key);
}



//EFFECTS:helper function to return the path from the root node to the node with value {key}.
bool findPath_helper(Node* root, const int &value, vector<string>* path) {
    if (!root) return false;
    if (root->getVal() == value) return true;
    bool flag = false;
    if(root->getLeft() && findPath_helper(root->getLeft(), value, path)) {
        path->push_back("0");
        flag = true;}
    if(root->getRight() && !flag && findPath_helper(root->getRight(), value, path)){
        path->push_back("1");
        flag = true;}
    return flag;}


//EFFECTS:Return the path from the root node to the node with value {key}.
std::string BinaryTree::findPath(const int &value) const {
    vector<string> path;
    path.emplace_back("");
    if(findPath_helper(root, value, &path)) {
        string string1;
        for (auto j = path.rbegin(); j != path.rend(); ++j)
            string1 += *j;
        return string1;
    } else
        return "-1";
}


//EFFECTS:helper function to return the terminal node if we can go through the tree starting from the root node and along the {path}.
Node* visitHelper(Node *node,const std::string &path,int index){
    if(node== nullptr){
        return nullptr;
    }else if(path.size()==index) {
        return node;
    } else if (node->getLeft()!= nullptr && path[index]=='0'){
        return visitHelper(node->getLeft(),path,index+1);
    } else if (node->getRight()!= nullptr && path[index]=='1'){
        return visitHelper(node->getRight(),path,index+1);
    } else return nullptr;
}


//EFFECTS:Return the terminal node if we can go through the tree starting from the root node and along the {path}.
Node * BinaryTree::visitThroughPath(const std::string &path) const {
    return visitHelper(this->root,path,0);
}



//EFFECTS:helper function to return the sum of the value of all nodes.
int sumHelper(Node* root) {
    if (!root)
        return 0;
    return sumHelper(root->getLeft()) + root->getVal() + sumHelper(root->getRight());
}


//EFFECTS:Return the sum of the value of all nodes in the tree.
int BinaryTree::sum() const {
    return sumHelper(this->root);
}



//EFFECTS:helper function to return the height of the node
int heightHelper(const Node *node) {
    if (!node)
        return 0;
    return heightHelper(node->getLeft()) > heightHelper(node->getRight()) ?
           heightHelper(node->getLeft()) + 1 : heightHelper(node->getRight()) + 1;
}



//EFFECTS:Return the height of the tree
int BinaryTree::height() const {
    return heightHelper(root);
}



//EFFECTS:Print the value of each node using a pre-order traversal.
void preOrderHelper(Node *node){
    if (!node) return;
    cout << node->getVal() << " ";
    preOrderHelper(node->getLeft());
    preOrderHelper(node->getRight());
}



//EFFECTS:Print the value of each node using a pre-order traversal.
void BinaryTree::preOrder() const {
    preOrderHelper(this->root);
    cout<<endl;
}


//EFFECTS:Print the value of each node using a in-order traversal.
void inOrderHelper(Node *node){
    if (!node) return;
    inOrderHelper(node->getLeft());
    cout << node->getVal() << " ";
    inOrderHelper(node->getRight());
}



//EFFECTS:Print the value of each node using a in-order traversal.
void BinaryTree::inOrder() const {
    inOrderHelper(this->root);
    cout<<endl;
}


//EFFECTS:Print the value of each node using a post-order traversal.
void postOrderHelper(Node *node){
    if (!node) return;
    postOrderHelper(node->getLeft());
    postOrderHelper(node->getRight());
    cout << node->getVal() << " ";
}



//EFFECTS:Print the value of each node using a post-order traversal.
void BinaryTree::postOrder() const {
    postOrderHelper(this->root);
    cout<<endl;
}



//EFFECTS:Return true if and only if for each root-to-leaf path of the node,
//     the sum of the value of all nodes along the path is greater than {sum}.
bool greaterHelper(Node *node,int sum){
    if (!node) return (sum > 0);
    if (!node->getLeft() && !node->getRight()) return node->getVal() > sum;
    return greaterHelper(node->getLeft(), sum - node->getVal()) && greaterHelper(node->getRight(), sum - node->getVal());

}

//EFFECTS:Return true if and only if for each root-to-leaf path of the tree,
//        the sum of the value of all nodes along the path is greater than {sum}.
bool BinaryTree::allPathSumGreater(const int &sum) const {
    return greaterHelper(this->root,sum);
}



//EFFECTS:Return true if this is covered by {tree}
bool cover(const Node *node1,const Node *node2){
    if (!node1) return true;
    if (!node2) return false;
    return node1->getVal() == node2->getVal() && cover(node1->getLeft(), node2->getLeft()) && cover(node1->getRight(), node2->getRight());
}



//EFFECTS:Return true if this is covered by {tree}
bool BinaryTree::operator<(const BinaryTree &tree) const {
    return cover(this->root,tree.root);
}



//EFFECTS:Return true if this is contained by {tree}
bool contain(const Node *node1, const Node *node2) {
    if (cover(node1, node2))
        return true;
    if (!node2)
        return false;
    return contain(node1, node2->getLeft()) || contain(node1, node2->getRight());
}



//EFFECTS:Return true if this is contained by {tree}
bool BinaryTree::operator<<(const BinaryTree &tree) const {
    return contain(root,tree.root);
}



//EFFECTS:"=" overloading
BinaryTree & BinaryTree::operator=(const BinaryTree &tree) {
    if(root!= nullptr){
        delete root;
        root= nullptr;
    }
    root=new Node(*tree.root);
    return *this;
}


Node *BinaryTree::createFromVariant(const vector<nodeValue> &source, const int &rootIndex) {
    if (rootIndex >= source.size())
        return nullptr;
    auto rootValue = get_if<int>(&source[rootIndex]);
    if (!rootValue)
        return nullptr;
    int rightIndex = 2 * (rootIndex + 1);
    int leftIndex = rightIndex - 1;
    return new Node(*rootValue, createFromVariant(source, leftIndex), createFromVariant(source, rightIndex));
}
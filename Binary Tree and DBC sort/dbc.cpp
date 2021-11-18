#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "BinaryTree.h"
#include "NodeInfo.h"
using namespace std;

void nodeConstructor(BinaryTree &tree, char &getPath,string& currentPath, int &nodeIndex, Node *currentNode)
//REQUIRES: tree is  not empty, current node has been initialized
//MODIFIES: tree, path, node, index
//EFFECTS:  construct new node for tree
{
    if(getPath=='0'){
        currentNode->setLeft(nodeIndex);
        cout<<"("<<currentNode->getVal()<<", "<<getPath<<')';
    } else{
        currentNode->setRight(nodeIndex);
        cout<<"("<<currentNode->getVal()<<", "<<getPath<<')';
    }
    currentPath="";
    nodeIndex++;
    //change the path and index
}

void judge(BinaryTree &tree, int &nodeIndex, char &getPath, string &currentPath, string &newPath)
//REQUIRES: tree is not empty
//MODIFIES: tree, path, index
//EFFECTS: judge whether the node is existed and construct a new node if not
{
    if(tree.visitThroughPath(newPath)){
        currentPath=newPath;
    } else{
        Node *currentNode(tree.visitThroughPath(currentPath));
        nodeConstructor(tree,getPath,currentPath,nodeIndex,currentNode);
    }
}

void compression(const string& filename)
//EFFECTS: compress the path to node information and cout;
{
    ifstream file;
    //Initialization
    string currentPath,newPath;
    char getPath;
    file.open(filename);
    BinaryTree tree;
    tree = BinaryTree(0);
    currentPath="";
    int nodeIndex=1;
    //Judgement and construct new node
    while (file.get(getPath)){
        string bar=currentPath;
        bar+=getPath;
        newPath=bar;
        judge(tree,nodeIndex,getPath,currentPath,newPath);
    }
    //output the last node
    Node *lastNode(tree.visitThroughPath(currentPath));
    cout<<"("<<lastNode->getVal()<<", @)";
    file.close();
}

void pathInfo(string &currentPath, BinaryTree &tree, NodeInfo &node, int &nodeIndex)
//REQUIRES: tree is not empty, node is initialized
//MODIFIES: path, node, tree, index
//EFFECTS: output the path of every node
{
    currentPath=tree.findPath(node.node_index);
    Node *currentNode(tree.visitThroughPath(currentPath));
    if(node.c=='0'){
        currentNode->setLeft(nodeIndex);
        cout<<tree.findPath(nodeIndex);
        nodeIndex++;
    } else if(node.c=='1'){
        currentNode->setRight(nodeIndex);
        cout<<tree.findPath(nodeIndex);
        nodeIndex++;
    } else {
        cout<<tree.findPath(node.node_index);
    }
}

void decompression(const string& filename)
//EFFECTS: read node in file and output their path
{
    ifstream file;
    string allRoot;
    file.open(filename);
    BinaryTree tree;
    tree = BinaryTree(0);
    NodeInfo node;
    node=NodeInfo();
    string currentPath;
    currentPath="";
    int nodeIndex=1;
    while (file>>node){
        pathInfo(currentPath,tree,node,nodeIndex);
    }
}


int main(int argc, char *argv[]){
    // TODO: implement your dbc program here!
    //Initialization
    string choice=argv[1];
    string filename=argv[2];
    //Judge the command and output information
    if(argc&&choice=="-x"){
        compression(filename);
    }
    if(argc&&choice=="-d"){
        decompression(filename);
    }
    return 0;
}
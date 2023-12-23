#include "AVLTree.h"
#include "Node.h"
#include <iostream>
#include<string>
#include<fstream>

using namespace std;

// constructor for the AVL tree
AVLTree::AVLTree(){ 
    root = nullptr;
}

//destructor for the AVL tree
AVLTree::~AVLTree(){
    deleteTree(root);
}

//Helper function to delete AVL tree
void AVLTree::deleteTree(Node* node){
    if(node != nullptr){
        deleteTree(node -> left);
        deleteTree(node -> right);
        delete node;
    }
}


void AVLTree::insert(const std::string& val) {
    //if the tree is empty, create the root
    if(root == nullptr){
      root = new Node(val);
      return;
    }
    // find the parent node of the node that is going to be inserted
    Node* parentOfVal = search(val, root);
    Node* child = new Node(val);
    child -> parent = parentOfVal;

    // insert the node as the left OR right child of parent
    if(val < parentOfVal -> data){
      parentOfVal -> left = child;
    }
    else if(val > parentOfVal -> data){
      parentOfVal -> right = child;
    } 
  else{ // if the value is already in the tree, return
    return;
  }

  // check for imabalances in the tree and perform rotations if needed
  Node* unbalancedNode = findUnbalancedNode(child);
  if (unbalancedNode != nullptr){
    rotate(unbalancedNode);
  }
  
}


void AVLTree::rotate(Node* node){
    // determine the balanceFactor for the node, left child of node, and the right child of node
    int balanceFactor1 = balanceFactor(node);
    int leftChildBalanceFactor = balanceFactor(node -> left);
    int rightChildBalanceFactor = balanceFactor(node -> right);

    // if the node is left heavy
    if(balanceFactor1 ==2){
        if(leftChildBalanceFactor == 1 || rightChildBalanceFactor == 1){ // It is a left left subtree and needs to be rotated right
            rotateRight(node);
        }
        else{ // It is a left right subtree and needs to be rotated left then right
            rotateLeft(node -> left);
            rotateRight(node);
        }
    }
    else{ //If the node is right heavy
        if (leftChildBalanceFactor == -1 || rightChildBalanceFactor == -1){ // It is a right right subtree and needs to be rotated left
            rotateLeft(node);
        }
        else { //It is a right left subtree and needs to be rotated right then left
            rotateRight(node -> right);
            rotateLeft(node);
        }

    }
}



Node *AVLTree::rotateLeft(Node* node){
  Node* rightLeftChild = node -> right -> left;
  if(node -> parent != nullptr){
    if(node -> parent -> right == node){ // right right subtree
      node -> parent -> right = node -> right; // Set the parent's right child to the node's right child
      if(node -> right != nullptr){ // if the node's right child is not null, set the node's right child's parent to the parent
        node -> right -> parent = node -> parent; 
      }
    }
    else if(node -> parent -> left == node){// left right subtree
      node -> parent -> left = node -> right; // Set the parent's left child to the node's right child
      if(node -> right != nullptr){ // if the node's right child is not null, set the node's right child's parent to the parent
        node -> right -> parent = node -> parent; 
      }
    }
  }
    else{ // if the node is the root
      root = node -> right;
      root -> parent = nullptr;
    }

    //Reconnection
    // Set the node's right child's left child to the node
    node -> right -> left = node;
    if(node != nullptr){ // if the node is not null, set the node's parent to the node's right child
      node -> parent = node -> right;
    }
    node -> right = rightLeftChild; // Set the node's right child to the right left child
    if(rightLeftChild != nullptr){ // if the right left child is not null, set the right left child's parent to the node
      rightLeftChild -> parent = node;
      
    }
    return node -> parent;

    
}

Node *AVLTree::rotateRight(Node* node){
    Node* leftRightChild = node -> left -> right;
    if(node -> parent != nullptr){
      if(node -> parent -> left == node){// left left subtree
        node -> parent -> left = node -> left; // Set the parent's left child to the node's left child
        if(node -> left != nullptr){ // if the node's left child is not null, set the node's left child's parent to the parent
          node -> left -> parent = node -> parent;
        }
      }
    else if(node -> parent -> right == node){ // right left subtree
      node -> parent -> right = node -> left; // Set the parent's right child to the node's left child
      if(node -> left != nullptr){ // if the node's left child is not null, set the node's left child's parent to the parent
        node -> left -> parent = node -> parent;
        }
      }
    }
    else{// this is the root
      root = node -> left;
      root -> parent = nullptr;
    }

    //reconnection
    // Set the node's left child's right child to the node
    node -> left -> right = node;
    if(node != nullptr){ // if the node is not null, set the node's parent to the node's left child
      node -> parent = node -> left;
    }
    node -> left = leftRightChild; // Set the node's left child to the left right child
    if(leftRightChild != nullptr){ // if the left right child is not null, set the left right child's parent to the node
        leftRightChild -> parent = node;
    }
    return node -> parent;
  
}


Node* AVLTree::search(const string &val, Node* node) const{ // searching for parent or where the new value should be inserted
    if(node -> data == val){ // If it's already in tree, return it
        return node;
    }
    if(val < node -> data){ // recursively search for the parent node 
        if(node -> left){
            return search(val, node -> left);
        }
        else{
            return node;
        }
    }
    else{
        if(node -> right){
            return search(val, node -> right);
        }
        else{
            return node;
        }
    }
}





int AVLTree::height(Node* node){
  if (node == nullptr) { // if the node is null
          return 0;
  }
  else{ // calculate the height of a given node
    return max(height(node -> left), height(node -> right)) + 1;
}
}
  

//calculate the balanceFactor of a node
int AVLTree::balanceFactor(Node* node){
    if (node == nullptr){
        return 0;
    }
    return height(node -> left) - height(node -> right);
}

//print the balance factor of a node
 void AVLTree::printBalanceFactors(Node* node){
    if (node != nullptr){
        printBalanceFactors(node -> left);
        cout << node -> data << "(" << balanceFactor(node) << "), ";
        printBalanceFactors(node -> right);
    }

 }

//print the balance factor of a node
 void AVLTree::printBalanceFactors() {
    printBalanceFactors(root);

 }

//find an unbalnced node starting from a given node
Node* AVLTree::findUnbalancedNode(Node* node){
    if (node == 0){
        return 0;
    }
    int Bfactor = balanceFactor(node);
    if (Bfactor == 2 || Bfactor == -2){
        return node;
    }
    else{
        return findUnbalancedNode(node -> parent);
    }
}


 void AVLTree::visualizeTree(const string &outputFilename){
     ofstream outFS(outputFilename.c_str());
     if(!outFS.is_open()){
         cout<<"Error"<<endl;
         return;
     }
     outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
     outFS<<"}";
     outFS.close();
     string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
     string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
     system(command.c_str());
 }

 void AVLTree::visualizeTree(ofstream & outFS, Node *n){
     if(n){
         if(n->left){
             visualizeTree(outFS,n->left);
             outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
         }

         if(n->right){
             visualizeTree(outFS,n->right);
             outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
         }
     }
 }


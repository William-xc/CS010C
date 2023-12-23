#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include "Node.h"
#include <string>
using namespace std;

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    AVLTree(const AVLTree& copy) = delete;
    AVLTree& operator=(const AVLTree& assign) = delete;
    void deleteTree(Node* node);
    void insert(const string& key);
    int balanceFactor(Node* node);
    void printBalanceFactors();
    void visualizeTree(const string &outputFilename);

private:
  Node* root;
  int height(Node* node);
  Node* rotateRight(Node* y);
  Node* rotateLeft(Node* x);
  void rotate(Node* node);
  void printBalanceFactors(Node* node) ;
  void visualizeTree(ofstream & outFS, Node *n);
  Node* findUnbalancedNode(Node* node);
 Node* search(const string& val, Node* node) const;
};


#endif 
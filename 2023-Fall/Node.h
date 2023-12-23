#ifndef NODE_H
#define NODE_H
#include<iostream>
#include <string>
using namespace std;


class Node {
public:
  string data;
  Node* left;
  Node* right;
  int height;
  Node* parent;
  Node(string data);
  Node();
};
#endif
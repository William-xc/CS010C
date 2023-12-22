#include "Node.h"
using namespace std;

Node::Node(string data) {
    this->data = data;
    left = 0;
    right = 0;
    height = 0;
    parent = 0;
}
Node::Node() {
    data = "";
    left = 0;
    right = 0;
    parent = 0;
    height = 0;
}
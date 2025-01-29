#ifndef NODE_H
#define NODE_H
#include <raylib.h>
#include <iostream>
using namespace std;

class Node {
    public:
        string name;
        Vector3 position;
        Node();
        ~Node();
};

#endif
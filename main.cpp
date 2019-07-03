/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: gudeh
 *
 * Created on 3 de Julho de 2019, 01:16
 */

#include "gde.h"
#include "mnist.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    graph graph_obj;
    mnist mnist_obj;
    string file_name;
    file_name="A1.aig";
    ifstream read(file_name.c_str(),ifstream::binary);
    graph_obj.readAIG(read,file_name);
    
    ifstream read_mnist("train-images.idx3-ubyte",ifstream::binary);
    mnist_obj.readIdx(read_mnist,"train-images.idx3-ubyte");
    mnist_obj.setBitsProbabilities(read_mnist);
    
//    graph_obj.setANDsProbabilities(mnist_obj);
//    graph_obj.propagateAndDeleteAll(mnist_obj);
    graph_obj.applyMnistRecursive(mnist_obj);
    return 0;
}


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

    string file_name;
    file_name="../A1.aig";
//    file_name="A1_ANDs_removed_1.aig";
//    file_name="andre.aig";
//    file_name="andre_ANDs_removed_1.aig";
    ifstream read,read_mnist;
    read.open(file_name.c_str(),ifstream::binary);
    
    mnist mnist_obj;
    graph graph_obj;
    
    float th=0;
    graph_obj.clearCircuit();
    graph_obj.setThrehsold(th);

    mnist_obj.clearMnist();
    read_mnist.close();
    read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
    mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
    mnist_obj.setBitsProbabilities(read_mnist);

    graph_obj.readAIG(read,file_name);
//    graph_obj.writeProbsHistogram();
    
    graph_obj.propagateAndDeleteAll(mnist_obj,0,0.9);
//    graph_obj.propagateAndDeletePIBased(mnist_obj);
//    graph_obj.setDepthsInToOut();
//        graph_obj.setANDsProbabilities(mnist_obj);

    graph_obj.applyMnistRecursive(mnist_obj);


//    mnist_obj.clearMnist();
//    read_mnist.close();
//    read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
//    mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
//    mnist_obj.setBitsProbabilities(read_mnist);
//    graph_obj.applyMnistRecursive(mnist_obj);
    
    
    for(float th=0.0001;th<=0.001;th=th+0.0001)
    {
      
        graph_obj.clearCircuit();
        graph_obj.setThrehsold(th);
        
        mnist_obj.clearMnist();
        read_mnist.close();
        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
        mnist_obj.setBitsProbabilities(read_mnist);
        
        graph_obj.readAIG(read,file_name);


//        graph_obj.setANDsProbabilities(mnist_obj);
        graph_obj.propagateAndDeleteAll(mnist_obj,0,0.9);
//        graph_obj.propagateAndDeletePIBased(mnist_obj);
//        graph_obj.setDepthsInToOut();
        graph_obj.applyMnistRecursive(mnist_obj);
        

//        mnist_obj.clearMnist();
//        read_mnist.close();
//        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        graph_obj.applyMnistRecursive(mnist_obj);
    }
    
        for(float th=0.0015;th<=0.0055;th=th+0.0005)
    {
      
        graph_obj.clearCircuit();
        graph_obj.setThrehsold(th);
        
        mnist_obj.clearMnist();
        read_mnist.close();
        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
        mnist_obj.setBitsProbabilities(read_mnist);
        
        graph_obj.readAIG(read,file_name);


//        graph_obj.setANDsProbabilities(mnist_obj);
        graph_obj.propagateAndDeleteAll(mnist_obj,0,0.9);
//        graph_obj.propagateAndDeletePIBased(mnist_obj);
        graph_obj.setDepthsInToOut();
//        graph_obj.applyMnistRecursive(mnist_obj);
//        
//
//        mnist_obj.clearMnist();
//        read_mnist.close();
//        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        graph_obj.applyMnistRecursive(mnist_obj);
    }
    return 0;
}


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
    
    float th=0,min_th=0.99;
//    vector<float> new_ths(5479,0);
//    ofstream dump("dump.txt");
//    for(int k=0;k<new_ths.size();k++)
//        new_ths[k]=((1-min_th)*((1+erf((6*k/(5479-1)) -3))/2))+min_th;
//    for(int k=0;k<new_ths.size();k++)
//        dump<<k<<":"<<new_ths[k]<<endl;
    
    mnist mnist_obj;
    graph graph_obj;
    int option=4,alpha=2;
    
    
    graph_obj.clearCircuit();
    graph_obj.setThrehsold(th);

    mnist_obj.clearMnist();
    read_mnist.close();
    read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
    mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
    mnist_obj.setBitsProbabilities(read_mnist);
//
    graph_obj.readAIG(read,file_name);
//    graph_obj.writeProbsHistogram();
    
//    graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha);
//    graph_obj.propagateAndDeletePIBased(mnist_obj);
//    graph_obj.setDepthsInToOut();
//        graph_obj.setANDsProbabilities(mnist_boj);
//
    graph_obj.applyMnistRecursive(mnist_obj);
//
//
//    mnist_obj.clearMnist();
//    read_mnist.close();
//    read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
//    mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
//    mnist_obj.setBitsProbabilities(read_mnist);
//    graph_obj.applyMnistRecursive(mnist_obj);
    
#if option ==1
    for(float th=0.0001;th<=0.001;th=th+0.0002)
    {
#else
    for(min_th=0.9999;min_th>=0.999;min_th-=0.0002)
    {
#endif
      
        graph_obj.clearCircuit();
        graph_obj.setThrehsold(th);
        
        mnist_obj.clearMnist();
        read_mnist.close();
        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
        mnist_obj.setBitsProbabilities(read_mnist);
        
        graph_obj.readAIG(read,file_name);


//        graph_obj.setANDsProbabilities(mnist_obj);
        graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha);
//        graph_obj.propagateAndDeletePIBased(mnist_obj);
//        graph_obj.setDepthsInToOut();
        graph_obj.applyMnistRecursive(mnist_obj);
        

        mnist_obj.clearMnist();
        read_mnist.close();
        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
        mnist_obj.setBitsProbabilities(read_mnist);
        graph_obj.applyMnistRecursive(mnist_obj);
    }

#if option ==1
    for(float th=0.0001;th<=0.001;th=th+0.0002)
    {
#else
    for(min_th=0.999;min_th>=0.99;min_th-=0.002)
    {
#endif
        graph_obj.clearCircuit();
        graph_obj.setThrehsold(th);
        
        mnist_obj.clearMnist();
        read_mnist.close();
        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
        mnist_obj.setBitsProbabilities(read_mnist);
        
        graph_obj.readAIG(read,file_name);
        
//        graph_obj.setANDsProbabilities(mnist_obj);
        graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha);
//        graph_obj.propagateAndDeletePIBased(mnist_obj);
//        graph_obj.setDepthsInToOut();
        graph_obj.applyMnistRecursive(mnist_obj);

        mnist_obj.clearMnist();
        read_mnist.close();
        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
        mnist_obj.setBitsProbabilities(read_mnist);
        graph_obj.applyMnistRecursive(mnist_obj);
    }
    return 0;
}


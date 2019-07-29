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
    ifstream read;
    mnist mnist_obj;
    
#if TRAIN_SET == 1
        ifstream read_mnist("../train-images.idx3-ubyte",ifstream::binary);
        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
        mnist_obj.setBitsProbabilities(read_mnist);
#else
        ifstream read_mnist("../t10k-images.idx3-ubyte",ifstream::binary);
        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
        mnist_obj.setBitsProbabilities(read_mnist);
#endif
    
    for(float th=0.0001;th<0.001;th=th+0.0001)
    {
#if TRAIN_SET == 0
        file_name="../A1_ANDs_removed_";
        file_name.append(to_string(1-th));
        file_name.append(".aig");
#endif
        read.open(file_name.c_str(),ifstream::binary);
//        float th=0;
        graph graph_obj(th);
        graph_obj.clearCircuit();
        graph_obj.readAIG(read,file_name);




    //    graph_obj.setANDsProbabilities(mnist_obj);
//        graph_obj.propagateAndDeleteAll(mnist_obj);
        graph_obj.applyMnistRecursive(mnist_obj);

    //    while(true)
    //    {
    //        int node_name;
    //        cout<<"Node?"<<endl;
    //        cin>>node_name;
    //        graph_obj.findAny(node_name)->printNode();
    //    }
//        graph_obj.~graph();
    }
    return 0;
}


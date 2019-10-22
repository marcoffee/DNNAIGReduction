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
    struct rusage buf;
    int start,stop;
    if(getrusage(RUSAGE_SELF,&buf)==-1)
        cout<<"GETRUSAGE FAILURE!"<<endl;
    start=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
    string file_name;
    file_name="../A1.aig";
//    file_name="andre.aag";

    ifstream read,read_mnist;
    read.open(file_name.c_str(),ifstream::binary);
    mnist mnist_obj;
    graph graph_obj;
    int option=1,alpha=2;
    float min_th=0.999;
   
//    vector<float> new_ths(5479,0);
//    ofstream dump("dump.txt");
//    for(int k=0;k<3000;k++)
//        new_ths[k]=-(((0.1)*k)/3000)+1;
//    
//    for(int k=0;k<new_ths.size();k++)
//        dump<<k<<":"<<new_ths[k]<<endl;
    


#if EXECUTE_ONCE ==1
    graph_obj.clearCircuit();
    graph_obj.setThrehsold(min_th);

    mnist_obj.clearMnist();
    read_mnist.close();
    read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
    mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
    mnist_obj.setBitsProbabilities(read_mnist);
    
    graph_obj.readAIG(read,file_name);
//    graph_obj.printCircuit();
//    graph_obj.readAAG(read,file_name);
  
    graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha);
//    graph_obj.propagateAndDeletePIBased(mnist_obj);
//    graph_obj.setDepthsInToOut();

    graph_obj.applyMnistRecursive(mnist_obj);


//    mnist_obj.clearMnist();
//    read_mnist.close();
//    read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
//    mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
//    mnist_obj.setBitsProbabilities(read_mnist);
//    graph_obj.applyMnistRecursive(mnist_obj);
    
    graph_obj.clearCircuit();
    graph_obj.readAIG(read,file_name);
    option=2;
    graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha);
    graph_obj.applyMnistRecursive(mnist_obj);
    
    graph_obj.clearCircuit();
    graph_obj.readAIG(read,file_name);
    option=3;
    graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha);
    graph_obj.applyMnistRecursive(mnist_obj);
   
    
#else

    for(min_th=0.9999;min_th>=0.999;min_th-=0.0002)
    {
      
        graph_obj.clearCircuit();
        graph_obj.setThrehsold(min_th);
        
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


    for(min_th=0.999;min_th>=0.99;min_th-=0.002)
    {
        graph_obj.clearCircuit();
        graph_obj.setThrehsold(min_th);
        
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
    
    for(min_th=0.99;min_th>=0.9;min_th-=0.02)
    {
        graph_obj.clearCircuit();
        graph_obj.setThrehsold(min_th);
        
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
#endif
    
    if(getrusage(RUSAGE_SELF,&buf)==-1)
        cout<<"GETRUSAGE FAILURE!"<<endl;
    stop=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
    cout<<"Time for whole process:"<<stop-start<<endl;
    return 0;
}


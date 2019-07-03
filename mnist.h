/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mnist.h
 * Author: augusto
 *
 * Created on 24 de Janeiro de 2019, 14:16
 */

#ifndef MNIST_H
#define MNIST_H

//#include "gde.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class mnist {
    vector <vector <vector <int> > > all_bits;
    vector <int> labels;
    vector <vector <float> > input_probabilities;
    
public:
    mnist();
    mnist(const mnist& orig);
    virtual ~mnist();
    
    int getBit(int img_index, int posY, int posX);
    int getLabel(int);
    vector <vector <vector <int> > > getAllBits();
    vector<vector<float> > getPIsProbabilities();
    
    void readIdx(ifstream&,string);
    void setBitsProbabilities(ifstream&);
private:

};

#endif /* MNIST_H */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gde.h
 * Author: augusto
 *
 * Created on 23 de Março de 2018, 16:56
 */

#ifndef GDE_H
#define GDE_H
//#define THRESHOLD 0

#define DBGVAR( os, var ) \
  (os) << "DBG: " << __FILE__ << "(" << __LINE__ << ") "\
       << #var << " = [" << (var) << "]" << std::endl
#define DEBUG 0
#define debug_value 2
#define SIMPLIFIEDAIG 1
#define TEST 0
#define IGNORE_OUTPUTS 0
#define PROBS_FROM_FILE 1
#define RENUMBER 1
#define LEAVE_CONSTANTS 0
#define FIX_DOUBLED_NODES 0



#define posY_max 28
#define posX_max 224

#define BITS_PACKAGE_SIZE 64

#include <vector>
#include <array>
#include <set>
#include <deque>
#include <stack>
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <limits.h> //char_bit
#include <algorithm> //max
#include <stdint.h> //uintptr_t
#include <functional> //reference_wraper
#include <sys/time.h>
#include <math.h> //pow
#include <sys/resource.h> //getrusage
#include <string.h> //strlen, strncmp
#include <bitset> //check bits on bit-parallel simulation
//#include "papi.h"
//#include "mypapi.h"
#include "mnist.h"

//#include "include/alice/alice.hpp"
using namespace std;









class node{
    
protected:
    unsigned int id;
    int signal;
    unsigned long long int bit_vector;
//    int depth;
    
public:
    node();
    node(unsigned int);
    virtual ~node();
    
    //modifiers
    virtual void pushOutput(node* param){}
    virtual void pushInput(node* param,bool param_polarity){}
    void setId(unsigned int);
    void setDepth(int);
    void setSignal(int);
    void setBitVector(unsigned long long int);
    
    //member access
    unsigned int getId();
    int getDepth();
    int getSignal();
    unsigned long long int getBitVector();
    node* fixLSB();    
    node* forceInvert();
    virtual vector<node*> getInputs(){}
    virtual vector<node*> getOutputs(){}
    virtual vector<int> getInputPolarities(){}
    
    
    //operations
    virtual int computeDepthInToOut(){}
    virtual unsigned int enumerateDFS(unsigned int index){} //TODO: this is not used anymore
    virtual unsigned long long int runDFS(){}
    //swap_index is the index from the input that will be replaced.
    virtual void replaceInput(int swap_index,node* new_node,bool polarity){}
//    virtual void removeOutput(node*){}
    virtual void removeOutput(unsigned int){}
//    virtual void recursiveRemoveOutput(unsigned int){}
    virtual void clearOutputs(){}
    
    
//    virtual void writeNode(){}
    virtual void writeNode(ofstream&){}
    //virtual int computeDepthOutToIn(){}
    
    virtual void printNode(){}
    
};








class input: public node {
    vector<node*> outputs;
    
public:
    input();
    using node::node; //enable use of constructor from node
    using node::setDepth;
    using node::getDepth;
    using node::getId;
    using node::getSignal;
   virtual ~input();
   
   //modifiers
   void pushOutput(node* param) override;
   
   //operations
   int computeDepthInToOut() override;
   unsigned int enumerateDFS(unsigned int index) override;
   unsigned long long int  runDFS() override;
//   void removeOutput(node* node_to_remove) override;
   void removeOutput(unsigned int id_to_remove) override;
//   void recursiveRemoveOutput(unsigned int id_to_remove) override;
   void clearOutputs() override;
   
   
   
//   void writeNode() override;
   void writeNode(ofstream&) override;
   void printNode() override;
   //member access
   vector<node*> getOutputs() override;
//   vector<bool> getInputPolarities() override;
   

   
};








class latch : public node{
    node* input;
    vector <node*> outputs;
public:
    //constructor
    latch();
    using node::node; //enable use of constructor from node
    virtual ~latch();
    
    //member access
    using node::getDepth;
    using node::getId;
    using node::getSignal;
//    int getInputPolarity();
    node* getInput();
    
    //modifiers
    using node::setDepth;
    void pushInput(node* param,bool param_polarity) override; 
    void pushOutput(node* param) override;

    //operations    
    int computeDepthInToOut() override;
    unsigned int enumerateDFS(unsigned int index) override;
//    unsigned int enumerateBFS(unsigned int index) override;
//    void writeNode() override;
    
};








class output : public node{
    node* input;
    
public:
    output();
    using node::node; //enable use of constructor from node
    virtual ~output();
    using node::setDepth;
    using node::getDepth;
    using node::getSignal;
    
    //modifiers
    void pushInput(node* param,bool param_polarity);
    void clearInput();
            
    //member access
    node* getInput();
    int getInputPolarity();
    
    //operations
//    void writeNode() override;
    void writeNode(ofstream&) override;
    int computeDepthInToOut() override;
    unsigned int enumerateDFS(unsigned int param_index) override;
    void printNode() override;
    unsigned long long int runDFS() override;

};



class AND : public node{
    vector <node*> inputs;
#if IGNORE_OUTPUTS == 0
    vector <node*> outputs;
#endif
    
public:
    AND();
    using node::node; 
    using node::setDepth;
    using node::getDepth;
    using node::getSignal;
    virtual ~AND();
    
    //member access
   vector<node*> getInputs() override; 
#if IGNORE_OUTPUTS == 0
       vector<node*> getOutputs() override;
#endif

   vector<int> getInputPolarities() override;
   
   //modifiers
   
   void pushInput(node* param,bool param_polarity) override;
   void replaceInput(int swap_index,node* new_node,bool polarity) override;
   void invertInputs();
   
   //operations
   int computeDepthInToOut() override;
   unsigned int enumerateDFS(unsigned int index) override;
   unsigned long long int runDFS() override;
   
#if IGNORE_OUTPUTS == 0
//   void removeOutput(node* node_to_remove) override;
   void removeOutput(unsigned int id_to_remove) override;
//   void recursiveRemoveOutput(unsigned int id_to_remove) override;
   void clearOutputs() override;
   void pushOutput(node* param) override;
#endif
   
   
//   void writeNode() override;
   void writeNode(ofstream&) override;
   void printNode() override;

};






class graph {
protected:
    map<unsigned int,input> all_inputs;
    map<unsigned int,latch> all_latches;
    map<unsigned int,output> all_outputs;
    map<unsigned int,AND> all_ANDS;
    string name;
    //Vector to store the probability of all ANDs
    map <unsigned int,float> ANDs_probabilities;
    //Original order of Primary Outputs
    vector<unsigned int> POs_order;
    //all_depths' index is the node ID/2 and the all_depths[ID/2] is the depth for this node.
     vector<unsigned int> all_depths;
    float threshold;
    int graph_depth;
    vector<unsigned int> greatest_depths_ids;
    node constant1,constant0;
    
    ofstream log;
    
   // mypapi papi_obj;
    
public:
    graph();
//    graph(float);
   virtual ~graph();
    
    
    //modifiers
    void readAAG(ifstream&,string);
    void readAIG(ifstream&,string);
    void setName(string);
    void setThrehsold(float);
    void clearCircuit();
    input* pushPI(unsigned int index,input input_obj);
    void pushLatch(unsigned int index,latch latch_obj);
    void pushPO(unsigned int index,output output_obj);
    AND* pushAnd(unsigned int index,AND AND_obj);
    void recursiveRemoveOutput(unsigned int id_to_remove,node* remove_from);
    
    //member access
    input* findInput(unsigned int);
    latch* findLatch(unsigned int);
    output* findOutput(unsigned int);
    AND* findAnd(unsigned int);
    node* findAny(unsigned int);
    map<unsigned int,input>* getInputs();
    map<unsigned int,latch>* getLatches();
    map<unsigned int,output>* getOutputs();
    map<unsigned int,AND>* getANDS();
    
    
    //operations
    void setDepthsInToOut();
    void setDepthsOutToIn();
    void writeAAG();
    void writeAIG();
    void writeProbsHistogram();
    void applyMnistRecursive(mnist&);
    void propagateAndDeletePIBased(mnist&);
    void cutAIG();
    void setANDsProbabilities(mnist&);
    void propagateAndDeleteAll(mnist&,int option,float min_th,int alpha);
    
    
    void assignBits(mnist&);
    
    
    //debugging
    void printCircuit();
    void printDepths();
    void writeCircuitDebug();
    
private:
    void encodeToFile(ofstream& file, unsigned x);
    unsigned char getnoneofch (ifstream& file,int);
    unsigned decode (ifstream& file,int);
    
    
};




class synthesizer : public graph{
    deque<node*> circ_deque;
    unsigned int M,I,L,O,A,AND_index;
    
private:
    void connectNodes(node* in, node* destination, bool invert);
    deque<node*> buildCellDeque(int num_inputs,bool input_inverted);
    
    void addAND(int num_inputs,bool balance);
    void addNAND(int num_inputs,bool balance);
    void addOR(int num_inputs,bool balance);
    void addNOR(int num_inputs,bool balance);
    void addXNOR(int num_inputs,bool balance);
    void addXOR(int num_inputs,bool balance);
    
    void enumerateGraph(int enumeration);
    void clearIDs();
    
    int parseLine(char*);
    int getValue();
    
public:
    synthesizer();
    ~synthesizer();
    
    
    //modifiers
    void create(int num_PI,int function,bool balance,int enumeration);
};



struct aux_struct{
    vector<node*> outputs;
    vector<bool> firsts_polarity;
};

//returns a word from a phrase, words are expected to be separeted by any number of blank spaces
string wordSelector(string line, int word_index);

//checks the pointer address passed as reference if it is inverted or not.
bool getThisPtrPolarity(node* param);

int binToDec(vector<int> param);

#endif /* GDE_H */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//
#include "gde.h"

output::output(){}

output::~output(){}


//void output::setPolarity(bool param) {
//    this->polarity=param;
//}



void output::pushInput(node* param, bool param_polarity) {
    //TRUE to invert FALSE to regular
    if(param_polarity)
            param=((node*)(((uintptr_t)param) ^ 01));
        input=param;
}

node* output::getInput(){
    return this->input->fixLSB();
}


int output::getInputPolarity(){
    return ((int)((uintptr_t)input) & 01);
}

void output::writeNode(ofstream& write){
    int depth;
//    ofstream write;
//    write.open("log.txt",ios::app);
    
    write<<"Output: "<<this->id+this->getInputPolarity()<<". Input:"<<this->getInput()->getId()<<endl;
}

int output::computeDepthInToOut(){
    int depth;
    ofstream write;

    depth=this->getInput()->computeDepthInToOut();

    return depth;
}


unsigned int output::enumerateDFS(unsigned int param_index) {
    this->id=param_index*2;
    
    return this->getInput()->enumerateDFS(param_index);
}

//unsigned int output::enumerateBFS(unsigned int param_index) {
//    this->id=param_index*2;
//    
//    return this->getInput()->enumerateBFS(param_index);
//}
        

void output::printNode(){
    cout<<"PO:"<<this->id<<". Input:";
        cout<<this->input->fixLSB()->getId()+(int)getThisPtrPolarity(input)<<",";
    cout<<endl;
}
        
unsigned long long int output::runDFS(){
//    cout<<"OUT "<<this->id<<"-";
    if(this->signal==-1)
        this->bit_vector=this->input->fixLSB()->runDFS();
        
    return this->signal;
}


void output::clearInput(){
    node* null_node=NULL;
    this->input=null_node;
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   node.cpp
 * Author: augusto
 * 
 * Created on 23 de Março de 2018, 17:00
 */

#include "AIG.h"

node::node() {
    this->id=0;
}

node::~node(){
}

node::node(unsigned int param){
    this->id=param;
//    this->depth=-1;
}

void node::setId(unsigned int param){
    this->id=param;
}

unsigned int node::getId(){
    return this->id;
}

void node::setDepth(int param){
    this->signal=param;
}

int node::getDepth(){
    return this->signal;
}

node* node::fixLSB(){
    return ((node*)(((uintptr_t)this) & ~01));
}


node* node::forceInvert(){
    return ((node*)(((uintptr_t)this) ^ 01));
}


void node::setSignal(int param){
    this->signal=param;
}

void node::setBitVector(unsigned long long int param) {
    this->bit_vector=param;
}

unsigned long long int node::getBitVector() {
    return this->bit_vector;
}



int node::getSignal(){
    return this->signal;
}
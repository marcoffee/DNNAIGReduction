#include "gde.h"
#include "mnist.h"
using namespace std;

void abcWrite(string new_name,string abc_name){
    cout<<endl<<"ABC WRITE: ("<<new_name<<") -> ("<<abc_name<<")"<<endl;
    ofstream script("script.scr");
    script<<"&r "<<new_name<<".aig"<<endl<<"&ps"<<endl<<"&w "<<abc_name<<endl<<"quit";
    script.close();
    system("./../abc -c 'source script.scr' >> log.txt ");
}

void abcCeC(string new_name,string abc_name,float min_th,int option){
    cout<<endl<<"ABC CEC: ("<<new_name<<") VS ("<<abc_name<<")"<<endl;
    ofstream script("script.scr"),log("log.txt",ios::app);
    script<<"&cec "<<new_name<<".aig "<<abc_name<<endl<<"quit";
    script.close();
    log<<"CEC on circuits: "<<new_name<<" VS: "<<abc_name<<endl<<"TH:"<<min_th<<", OPTION:"<<option<<endl;
    log.close();
    system("./../abc -c 'source script.scr' >> log.txt");
}


int main(int argc, char** argv) {
    struct rusage buf;
    int start,stop,start_simplf,stop_simplf,start_app,stop_app,iterations=0;
    if(getrusage(RUSAGE_SELF,&buf)==-1)
        cout<<"GETRUSAGE FAILURE!"<<endl;
    start=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
    string file_name,new_name,abc_name;
#if TEST == 0
    file_name="../A1.aig";;
#elif TEST == 1
    file_name="andre.aig";;
#endif
//    file_name="ABC_andre_NO_CONSTANTS_ANDs_removed_FIXED_.aig";
    ofstream dump_append("dump_append.txt"),exec_times("exec_times.csv"),script("script.scr"),log("log.txt"),abc_info("abc_info.txt"),nodes_file("Nodes_in_level.csv");
    log.close(); dump_append.close(); nodes_file.close();
    ifstream read,read_mnist;
    read.open(file_name.c_str(),ifstream::binary);
    mnist mnist_obj;
    graph graph_obj;
    int option,alpha=2,LEAVE_CONSTANTS=0;
    float min_th=0.9999;
    stringstream ss(argv[1]);  ss>>option;
    cout<<"Setting option to:"<<option<<endl;
          
    //1->linear, 2->root, 3->exp, 4->sigmod, 51->#nodes_linear, 52->#nodes_root,53->#nodes_exp
#if APPLY_MNIST == 1
    exec_times<<"Otption:"<<option<<", Circuit:"<<file_name<<endl<<"Min_th, Set Constants, Train Set ABC, Test Set ABC, My Simplification, Train Set, Test Set"<<endl;
#else
    exec_times<<"Otption:"<<option<<", Circuit:"<<file_name<<endl<<"Min_th, Set Constants, My Simplification"<<endl;
#endif
#if EXECUTE_ONCE == 3
//    cout<<"threhsold:"<<min_th<<", 1-threshold:"<<(float)1-min_th<<endl;
//    cout<<"Calculating th_inverted:"<<endl;
//    float th_inverted=min_th;
//    int aux;
//    cout<<"th_inverted=min_th:"<<th_inverted<<endl;
//    aux=th_inverted*10000;
//    cout<<"aux=th_inverted*10000:"<<aux<<endl;
//    aux=10000-aux;
//    cout<<"aux=10000-aux:"<<aux<<endl;
//    th_inverted=(aux/(float)10000);
//    cout<<"th_inverted=aux/10000:"<<th_inverted<<endl;
//    
//    vector<float> new_ths(5479,0);
//    ofstream dump("dump.txt");
//    for(int k=0;k<3000;k++)
//        new_ths[k]=-(((0.1)*k)/3000)+1;
//    
//    for(int k=0;k<new_ths.size();k++)
//        dump<<k<<":"<<new_ths[k]<<endl;
//    unsigned long long int bits1,bits2,result;
//    unsigned int id1=UINT_MAX,id2=1024;
//    
//    bits2=(unsigned long long int)id2;
//    bits1=(unsigned long long int)id1;
//    bitset<64> x(bits1),y(bits2),z(id2);
//    
//    result=(bits1 << 32) | bits2;
//    cout<<result<<endl;
//    bitset<64> w(result);
//    cout<<w<<endl;
//     cout<<id1<<","<<(unsigned long long int)id1<<","<<bits1<<endl;
//    cout<<x<<","<<y<<","<<z<<endl;
    
//    vector<int> depth_counter<0,5479>;
//    
//    int biggest=3000;
//    
//    {
//        for(int k=0;k<new_ths.size();k++)
//            new_ths[k]=(th_inverted*(-pow((((float)depth_counter[k])/(biggest-1)),alpha)+((float)biggest/(biggest-1))))+min_th;
//    }
//    system("./../abc -c 'source script.scr'");;

#elif EXECUTE_ONCE ==1
/////////////////////////////////Generating file WITH CONSTANTS to go trhough ABC/////////////////////////////////////////////////
//        mnist_obj.clearMnist();
//        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        read_mnist.close();
//        
//        graph_obj.clearCircuit();
//        graph_obj.setThrehsold(min_th);        
//        graph_obj.readAIG(read,file_name);
//
//        LEAVE_CONSTANTS=0;  
//        getrusage(RUSAGE_SELF,&buf); start_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha,LEAVE_CONSTANTS);
//        getrusage(RUSAGE_SELF,&buf); stop_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<min_th<<","<<((stop_simplf-start_simplf)/(float)3600)<<",";
//        graph_obj.writeAIG();
//        
//        new_name=graph_obj.getName();
//        abc_name="ABC_"+new_name+".aig";
//        abcWrite(new_name,abc_name);  
//        
//        graph_obj.clearCircuit(); read.close(); read.open(abc_name.c_str(),ifstream::binary);
//        graph_obj.setThrehsold(min_th);        
//        graph_obj.readAIG(read,abc_name); graph_obj.setDepthsInToOut();
//        abc_info<<graph_obj.getName()<<","<<min_th<<","<<graph_obj.getDepth()<<","<<graph_obj.getANDS()->size()<<endl;
//#if APPLY_MNIST == 0
//        graph_obj.clearCircuit();
//        graph_obj.setThrehsold(min_th);        
//        graph_obj.readAIG(read,abc_name);
//        
//        getrusage(RUSAGE_SELF,&buf);  start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.applyMnistRecursive(mnist_obj);
//        getrusage(RUSAGE_SELF,&buf);  stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<((stop_app-start_app)/(float)3600)<<",";
//        
//        mnist_obj.clearMnist();
//        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        read_mnist.close();
//        getrusage(RUSAGE_SELF,&buf); start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.applyMnistRecursive(mnist_obj);
//        getrusage(RUSAGE_SELF,&buf); stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<((stop_app-start_app)/(float)3600)<<",";
//#endif  
//#if CEC == 1
///////////////////////////////Generating file with my own simplification/////////////////////////////////////////////////
//        mnist_obj.clearMnist();
//        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        read_mnist.close();
//
//        graph_obj.clearCircuit();
//        graph_obj.setThrehsold(min_th);
//        graph_obj.readAIG(read,file_name);
//
//        LEAVE_CONSTANTS=0;
//        getrusage(RUSAGE_SELF,&buf); start_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha,LEAVE_CONSTANTS);
//        getrusage(RUSAGE_SELF,&buf); stop_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<((stop_simplf-start_simplf)/(float)3600)<<",";
//        graph_obj.writeAIG();
//
//        new_name=graph_obj.getName(); 
//        abcCeC(new_name,abc_name,min_th,option); 
//
//#if APPLY_MNIST == 0
////        getrusage(RUSAGE_SELF,&buf);  start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        graph_obj.applyMnistRecursive(mnist_obj);
////        getrusage(RUSAGE_SELF,&buf);  stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        exec_times<<((stop_app-start_app)/(float)3600)<<",";
////
////        mnist_obj.clearMnist();
////        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
////        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
////        mnist_obj.setBitsProbabilities(read_mnist);
////        read_mnist.close();
////        getrusage(RUSAGE_SELF,&buf); start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        graph_obj.applyMnistRecursive(mnist_obj);
////        getrusage(RUSAGE_SELF,&buf); stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        exec_times<<((stop_app-start_app)/(float)3600)<<",";
//#endif
//#endif
//        exec_times<<endl;

#elif EXECUTE_ONCE == 0

//    for(min_th=0.9999;min_th>0.999;min_th-=0.0001)
//    {
/////////////////////////////////Generating file WITH CONSTANTS to go trhough ABC/////////////////////////////////////////////////
//        cout<<"//////////////////////////"<<endl<<"/////////"<<min_th<<"///////////"<<endl<<"//////////////////////////"<<endl;
//        mnist_obj.clearMnist();
//        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        read_mnist.close();
//        
//        graph_obj.clearCircuit(); read.close(); read.open(file_name.c_str(),ifstream::binary);
//        graph_obj.setThrehsold(min_th);        
//        graph_obj.readAIG(read,file_name);
//
//        LEAVE_CONSTANTS=1;  
//        getrusage(RUSAGE_SELF,&buf); start_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha,LEAVE_CONSTANTS);
//        getrusage(RUSAGE_SELF,&buf); stop_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<min_th<<","<<((stop_simplf-start_simplf)/(float)3600)<<",";
//        graph_obj.writeAIG();
//        
//        new_name=graph_obj.getName();
//        abc_name="ABC_"+new_name+".aig";
//        abcWrite(new_name,abc_name);  
//        
//        graph_obj.clearCircuit(); read.close(); read.open(abc_name.c_str(),ifstream::binary);
//        graph_obj.setThrehsold(min_th);        
//        graph_obj.readAIG(read,abc_name); graph_obj.setDepthsInToOut();
//        abc_info<<graph_obj.getName()<<","<<min_th<<",option:"<<option<<","<<graph_obj.getDepth()<<","<<graph_obj.getANDS()->size()<<endl;
//#if APPLY_MNIST == 1
//        cout<<"APPLYING MNIST WITH ABC's SIMPLIFICATION -> ";
//        graph_obj.clearCircuit(); read.close(); read.open(abc_name.c_str(),ifstream::binary);
//        graph_obj.setThrehsold(min_th);        
//        graph_obj.readAIG(read,abc_name);
//        
//        getrusage(RUSAGE_SELF,&buf);  start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.applyMnistRecursive(mnist_obj);
//        getrusage(RUSAGE_SELF,&buf);  stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TRAIN DONE, ";
//        
//        mnist_obj.clearMnist();
//        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        read_mnist.close();
//        getrusage(RUSAGE_SELF,&buf); start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.applyMnistRecursive(mnist_obj);
//        getrusage(RUSAGE_SELF,&buf); stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TEST DONE, "<<endl;
//#endif  
//#if CEC == 1
///////////////////////////////Generating file with my own simplification/////////////////////////////////////////////////
//        mnist_obj.clearMnist();
//        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        read_mnist.close();
//
//        graph_obj.clearCircuit(); read.close(); read.open(file_name.c_str(),ifstream::binary);
//        graph_obj.setThrehsold(min_th);
//        graph_obj.readAIG(read,file_name);
//
//        LEAVE_CONSTANTS=0;
//        getrusage(RUSAGE_SELF,&buf); start_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha,LEAVE_CONSTANTS);
//        getrusage(RUSAGE_SELF,&buf); stop_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<((stop_simplf-start_simplf)/(float)3600)<<",";
//        graph_obj.writeAIG();
//
//        new_name=graph_obj.getName(); 
//        abcCeC(new_name,abc_name,min_th,option);
//        ofstream csv_final; csv_final.open("todos_scores.csv",ios::app); csv_final<<endl;
//#if APPLY_MNIST == 1
//        cout<<"APPLYING MNIST WITH MY OWN SIMPLIFICATION"<<endl;
////        getrusage(RUSAGE_SELF,&buf);  start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        graph_obj.applyMnistRecursive(mnist_obj);
////        getrusage(RUSAGE_SELF,&buf);  stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TRAIN DONE, ";
////
////        mnist_obj.clearMnist();
////        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
////        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
////        mnist_obj.setBitsProbabilities(read_mnist);
////        read_mnist.close();
////        getrusage(RUSAGE_SELF,&buf); start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        graph_obj.applyMnistRecursive(mnist_obj);
////        getrusage(RUSAGE_SELF,&buf); stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TEST DONE, "<<endl;
//#endif
//#endif
//        exec_times<<endl;
//        iterations++;
//    }
//
//
//    for(min_th=0.999;min_th>0.99;min_th-=0.001)
//    {
/////////////////////////////////Generating file WITH CONSTANTS to go trhough ABC/////////////////////////////////////////////////
//        cout<<"//////////////////////////"<<endl<<"/////////"<<min_th<<"///////////"<<endl<<"//////////////////////////"<<endl;
//        mnist_obj.clearMnist();
//        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        read_mnist.close();
//        
//        graph_obj.clearCircuit(); read.close(); read.open(file_name.c_str(),ifstream::binary);
//        graph_obj.setThrehsold(min_th);        
//        graph_obj.readAIG(read,file_name);
//
//        LEAVE_CONSTANTS=1;  
//        getrusage(RUSAGE_SELF,&buf); start_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha,LEAVE_CONSTANTS);
//        getrusage(RUSAGE_SELF,&buf); stop_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<min_th<<","<<((stop_simplf-start_simplf)/(float)3600)<<",";
//        graph_obj.writeAIG();
//        
//        new_name=graph_obj.getName();
//        abc_name="ABC_"+new_name+".aig";
//        abcWrite(new_name,abc_name);  
//        
//        graph_obj.clearCircuit(); read.close(); read.open(abc_name.c_str(),ifstream::binary);
//        graph_obj.setThrehsold(min_th);        
//        graph_obj.readAIG(read,abc_name); graph_obj.setDepthsInToOut();
//        abc_info<<graph_obj.getName()<<","<<min_th<<",option:"<<option<<","<<graph_obj.getDepth()<<","<<graph_obj.getANDS()->size()<<endl;
//#if APPLY_MNIST == 1
//        cout<<"APPLYING MNIST WITH ABC's SIMPLIFICATION -> ";
//        graph_obj.clearCircuit(); read.close(); read.open(abc_name.c_str(),ifstream::binary);
//        graph_obj.setThrehsold(min_th);        
//        graph_obj.readAIG(read,abc_name);
//        
//        getrusage(RUSAGE_SELF,&buf);  start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.applyMnistRecursive(mnist_obj);
//        getrusage(RUSAGE_SELF,&buf);  stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TRAIN DONE, ";
//        
//        mnist_obj.clearMnist();
//        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        read_mnist.close();
//        getrusage(RUSAGE_SELF,&buf); start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.applyMnistRecursive(mnist_obj);
//        getrusage(RUSAGE_SELF,&buf); stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TEST DONE, "<<endl;
//#endif  
//#if CEC == 1
///////////////////////////////Generating file with my own simplification/////////////////////////////////////////////////
//        mnist_obj.clearMnist();
//        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        read_mnist.close();
//
//        graph_obj.clearCircuit(); read.close(); read.open(file_name.c_str(),ifstream::binary);
//        graph_obj.setThrehsold(min_th);
//        graph_obj.readAIG(read,file_name);
//
//        LEAVE_CONSTANTS=0;
//        getrusage(RUSAGE_SELF,&buf); start_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha,LEAVE_CONSTANTS);
//        getrusage(RUSAGE_SELF,&buf); stop_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<((stop_simplf-start_simplf)/(float)3600)<<",";
//        graph_obj.writeAIG();
//
//        new_name=graph_obj.getName(); 
//        abcCeC(new_name,abc_name,min_th,option);
//        ofstream csv_final; csv_final.open("todos_scores.csv",ios::app); csv_final<<endl;
//#if APPLY_MNIST == 1
//        cout<<"APPLYING MNIST WITH MY OWN SIMPLIFICATION"<<endl;
////        getrusage(RUSAGE_SELF,&buf);  start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        graph_obj.applyMnistRecursive(mnist_obj);
////        getrusage(RUSAGE_SELF,&buf);  stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TRAIN DONE, ";
////
////        mnist_obj.clearMnist();
////        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
////        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
////        mnist_obj.setBitsProbabilities(read_mnist);
////        read_mnist.close();
////        getrusage(RUSAGE_SELF,&buf); start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        graph_obj.applyMnistRecursive(mnist_obj);
////        getrusage(RUSAGE_SELF,&buf); stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
////        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TEST DONE, ";
//#endif
//#endif
//        exec_times<<endl;
//        iterations++;
//    }
    
    for(min_th=0.95;min_th>=0.9;min_th-=0.01)
    {
///////////////////////////////Generating file WITH CONSTANTS to go trhough ABC/////////////////////////////////////////////////
        cout<<"//////////////////////////"<<endl<<"/////////"<<min_th<<"///////////"<<endl<<"//////////////////////////"<<endl;
        mnist_obj.clearMnist();
        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
        mnist_obj.setBitsProbabilities(read_mnist);
        read_mnist.close();
        
        graph_obj.clearCircuit(); read.close(); read.open(file_name.c_str(),ifstream::binary);
        graph_obj.setThrehsold(min_th);        
        graph_obj.readAIG(read,file_name);

        LEAVE_CONSTANTS=1;  
        getrusage(RUSAGE_SELF,&buf); start_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
        graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha,LEAVE_CONSTANTS);
        getrusage(RUSAGE_SELF,&buf); stop_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
        exec_times<<min_th<<","<<((stop_simplf-start_simplf)/(float)3600)<<",";
        graph_obj.writeAIG();
        
        new_name=graph_obj.getName();
        abc_name="ABC_"+new_name+".aig";
        abcWrite(new_name,abc_name);  
        
        graph_obj.clearCircuit(); read.close(); read.open(abc_name.c_str(),ifstream::binary);
        graph_obj.setThrehsold(min_th);        
        graph_obj.readAIG(read,abc_name); graph_obj.setDepthsInToOut();
        abc_info<<graph_obj.getName()<<","<<min_th<<",option:"<<option<<","<<graph_obj.getDepth()<<","<<graph_obj.getANDS()->size()<<endl;
#if APPLY_MNIST == 1
        cout<<"APPLYING MNIST WITH ABC's SIMPLIFICATION -> ";
        graph_obj.clearCircuit(); read.close(); read.open(abc_name.c_str(),ifstream::binary);
        graph_obj.setThrehsold(min_th);        
        graph_obj.readAIG(read,abc_name);
        
        getrusage(RUSAGE_SELF,&buf);  start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
        graph_obj.applyMnistRecursive(mnist_obj);
        getrusage(RUSAGE_SELF,&buf);  stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TRAIN DONE, ";
        
        mnist_obj.clearMnist();
        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
        mnist_obj.setBitsProbabilities(read_mnist);
        read_mnist.close();
        getrusage(RUSAGE_SELF,&buf); start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
        graph_obj.applyMnistRecursive(mnist_obj);
        getrusage(RUSAGE_SELF,&buf); stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TEST DONE, "<<endl;
#endif  
#if CEC == 1
/////////////////////////////Generating file with my own simplification/////////////////////////////////////////////////
        mnist_obj.clearMnist();
        read_mnist.open("../train-images.idx3-ubyte",ifstream::binary);
        mnist_obj.readIdx(read_mnist,"../train-images.idx3-ubyte");
        mnist_obj.setBitsProbabilities(read_mnist);
        read_mnist.close();

        graph_obj.clearCircuit(); read.close(); read.open(file_name.c_str(),ifstream::binary);
        graph_obj.setThrehsold(min_th);
        graph_obj.readAIG(read,file_name);

        LEAVE_CONSTANTS=0;
        getrusage(RUSAGE_SELF,&buf); start_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
        graph_obj.propagateAndDeleteAll(mnist_obj,option,min_th,alpha,LEAVE_CONSTANTS);
        getrusage(RUSAGE_SELF,&buf); stop_simplf=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
        exec_times<<((stop_simplf-start_simplf)/(float)3600)<<",";
        graph_obj.writeAIG();

        new_name=graph_obj.getName(); 
        abcCeC(new_name,abc_name,min_th,option);
        ofstream csv_final; csv_final.open("todos_scores.csv",ios::app); csv_final<<endl;
#if APPLY_MNIST == 1
        cout<<"APPLYING MNIST WITH MY OWN SIMPLIFICATION"<<endl;
//        getrusage(RUSAGE_SELF,&buf);  start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.applyMnistRecursive(mnist_obj);
//        getrusage(RUSAGE_SELF,&buf);  stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TRAIN DONE, ";
//
//        mnist_obj.clearMnist();
//        read_mnist.open("../t10k-images.idx3-ubyte",ifstream::binary);
//        mnist_obj.readIdx(read_mnist,"../t10k-images.idx3-ubyte");
//        mnist_obj.setBitsProbabilities(read_mnist);
//        read_mnist.close();
//        getrusage(RUSAGE_SELF,&buf); start_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        graph_obj.applyMnistRecursive(mnist_obj);
//        getrusage(RUSAGE_SELF,&buf); stop_app=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
//        exec_times<<((stop_app-start_app)/(float)3600)<<","; cout<<"TEST DONE, ";
#endif
#endif
        exec_times<<endl;
        iterations++;
    }
#endif
    ifstream check_log("log.txt"); string line; int equivalent_count=0;
    while(getline(check_log,line))
    {
        if(line.find("Networks are equivalent")!=string::npos)
            equivalent_count++;
    }
    cout<<"AIGs processed:"<<iterations<<", CECs passed:"<<equivalent_count<<endl;
    
    if(getrusage(RUSAGE_SELF,&buf)==-1)
        cout<<"GETRUSAGE FAILURE!"<<endl;
    stop=buf.ru_stime.tv_sec+buf.ru_utime.tv_sec;
    cout<<"Time for whole process:"<<((stop-start)/(float)3600)<<endl;
    return 0;
}


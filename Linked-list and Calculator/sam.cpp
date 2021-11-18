#include <algorithm>
#include <iostream>
#include <string>
#include "Dlist.h"
#include "Instr.h"
#include <sstream>
using namespace std;
const int MEMBER=16;

//EFFECTS: detect whether "-s" exists in the argument
bool sDetect(int argc,char *argv[]){
    bool detect= false;
    string s="-s";
    for(int i=0;i<argc;i++){
        if(argv[i]==s){
            detect= true;
        }
    }
    return detect;
}

//EFFECTS: read the the number in the stack and queue from the first line
void numGet(int &sNum,int &qNum,const string& numLine){
    unsigned int len=numLine.length();
    for(unsigned int i=0;i<len;i++){
        if(numLine[i]==' '){
            sNum= stoi(numLine.substr(0,i));
            qNum= stoi(numLine.substr(i+1,len));
        }
    }
}

//MODIFIES: stack
//EFFECTS: push the number into the stack
void stackGet(stack &numStack,const string& sLine,int sNum){
    stringstream ss;
    ss.str(sLine);
    string numLine[sNum];
    int i=0,num;
    while(ss>>numLine[i]){
        num=stoi(numLine[i]);
        numStack.push(num);
        i++;
    }
}

//MODIFIES: queue
//EFFECTS: push the instructions into the queue
void queueGet(queue &insQueue, int qNum){
    Instr ins[qNum];
    for(int i=0;i<qNum;i++){
        cin>>ins[i];
        insQueue.push(ins[i]);
    }
}

//MODIFIES: stack,queue,memory
//EFFECTS: use previous functions to push number and instructions into the cotainers
void infoPush(stack &numStack,queue &insQueue,int memory[MEMBER],int &sNum,int &qNum){
    string num,stackLine,memoryLine;
    getline(cin,num);
    numGet(sNum,qNum,num);
    getline(cin,stackLine);
    stackGet(numStack,stackLine,sNum);
    queueGet(insQueue,qNum);
    for(int i=0;i<MEMBER;i++){
        cin>>memory[i];
    }
}

//MODIFIES: stack,queue
//EFFECTS: show the number and instructions in the stack and queue and memory
void showInfo(stack& numStack,queue& insQueue,int memory[MEMBER]){
    numStack.showInfo();
    insQueue.showInfo();
    for(int i=0;i<MEMBER;i++){ cout<<memory[i]<<' ';}
    cout<<endl;
}

//MODIFIES: stack
//EFFECTS: pop two number from stack, add them and push in
void add(stack &numStack){
    int a,b;
    a=numStack.pop();
    b=numStack.pop();
    b=b+a;
    numStack.push(b);
}

//MODIFIES: stack
//EFFECTS: pop two number from stack, nor them and push in
void nor(stack& numStack){
    int a,b;
    a=numStack.pop();
    b=numStack.pop();
    b=~(a|b);
    numStack.push(b);
}
//MODIFIES: stack
//EFFECTS: pop one number from stack
void Pop(stack& numStack){ numStack.pop();}

//MODIFIES: stack
//EFFECTS: push one number into stack
void Push(stack& numStack,Instr &instr){
    int num=instr.parameter;
    numStack.push(num);
}

//MODIFIES: stack,memory
//EFFECTS: implementation of load function
void load(stack& numStack,const int memory[MEMBER]){
    int old=numStack.pop();
    int newNum=memory[old];
    numStack.push(newNum);
}

//MODIFIES: stack,memory
//EFFECTS: implementation of store function
void store(stack& numStack,int memory[MEMBER]){
    int add=numStack.pop();
    int newNum=numStack.pop();
    memory[add]=newNum;
}
//MODIFIES: stack,memory,queue
//EFFECTS: implementation of ifz function
void ifz(stack& numStack,queue &insQueue,Instr &instr){
    int num=instr.parameter;
    int numGet=numStack.pop();
    if(numGet==0){
        for(int i=0;i<num;i++){
            insQueue.pop();
        }
    }
}

//MODIFIES: stack,memory,queue
//EFFECTS: judge the instruction and deal the member in the containers
void deal(Instr instr,stack &numStack,queue &insQueue,int memory[MEMBER],bool &on){
    cout<<instr<<endl;
    if(instr.name==InstrName::ADD) add(numStack);
    if(instr.name==InstrName::STORE) store(numStack,memory);
    if(instr.name==InstrName::NOR) nor(numStack);
    if(instr.name==InstrName::PUSHI) Push(numStack,instr);
    if(instr.name==InstrName::LOAD) load(numStack,memory);
    if(instr.name==InstrName::IFZ) ifz(numStack,insQueue,instr);
    if(instr.name==InstrName::POP) Pop(numStack);
    if(instr.name==InstrName::HALT){
        showInfo(numStack,insQueue,memory);
        on= false;
        return;
    }
}

//MODIFIES: stack,memory,queue
//EFFECTS: output complete result of every dealing
void output(stack &numStack,queue &insQueue,int memory[MEMBER]){
    bool on=true;
    int stackNum,queueNum;
    infoPush(numStack,insQueue,memory,stackNum,queueNum);
    int num=queueNum;
    while (on){
    for(int i=0;i<num;i++){
        Instr instr=insQueue.pop();
        deal(instr,numStack,insQueue,memory,on);
        if(on)showInfo(numStack,insQueue,memory);
    }}
}

//MODIFIES: stack,memory,queue
//EFFECTS: output simple result of dealing
void sOutput(stack &numStack,queue &insQueue,int memory[MEMBER]){
    bool on= true;
    int stackNum,queueNum;
    infoPush(numStack,insQueue,memory,stackNum,queueNum);
    int num=queueNum;
    while (on){
    for(int i=0;i<num;i++){
        Instr instr=insQueue.pop();
        deal(instr,numStack,insQueue,memory,on);
    }}
}


int main(int argc, char *argv[])
{
    //TODO:write your code here.
    stack numStack;
    queue insQueue;
    int memory[MEMBER];
    //judge the type of output
    if(!sDetect(argc,argv)){
        //output complete result
        output(numStack,insQueue,memory);
        //output simple result
    } else sOutput(numStack,insQueue,memory);
    return 0;
}

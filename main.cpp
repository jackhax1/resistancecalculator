#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;


void enterFormula(string& eqn){
    cout<<"Enter circuit formula: ";
    cin>>eqn;
}

double todouble(string x){

    bool dec=false;
    int multiple=0;
    double num=0;
    int i=0;
    while(x[i]!='\0'){
        if(x[i]=='.'){
            dec=true;
            multiple=-1;
            i++;
        }
        if (!dec){
            num = num*pow(10,multiple) + (x[i] -'0');
            multiple++;
            i++;
        }
        if(dec){
            num = num +(x[i]-'0')*pow(10,multiple);
            multiple--;
            i++;
        }
    }
    return num;
}

void generateRandom(int numofresistor,double number[],int oper[],string &eqn){
    int randoperator,randomnumber;

    srand(time(0));

    for(int i=0;i<numofresistor;i++){
        number[i]=rand()%100+1;
        eqn += to_string(number[i]);

        if(i<numofresistor-1){
            oper[i]=rand()%2+1;
            if(oper[i]==1)
                eqn += '/';
            if(oper[i]==2)
                eqn += '+';
        }
    }
}

void showEqn(string eqn){
    cout<<"Circuit formula is "<<eqn<<endl;
}

void showEqnrand(double number[],int oper[],int numofresistor){
    for(int i=0;i<numofresistor;i++){
        cout<<fixed<<setprecision(1)<<number[i];
        if(i<numofresistor-1){
            if(oper[i]==1)
                cout<<'/';
            else
                cout<<'+';
        }
    }
    cout<<endl;
}

void calculateResistance(string eqn){

    int i=0, j=0, k=0, q=0, parallel=0, series=0;

    while(eqn[q]!='\0'){  //check how many of each operators in the eqn
        if(eqn[q]=='/')
            parallel++;
        if(eqn[q]=='+')
            series++;
        q++;
    }

    int x=series+parallel;

    int oper[x]={};
    double number[x+1]={};

    j=0;
    k=0;

    while(eqn[i]!='\0'){ //separate the values and the operators
        if(eqn[i]=='/'){ //separate operator '/'
            oper[k]=1;
            k++;
        }
        if(eqn[i]=='+'){ //separate operator '+'
            oper[k]=2;
            k++;
        }

        if(eqn[i]=='/'||eqn[i]=='\0'||eqn[i]=='+'){ //values are separated here
            number[j]=todouble(eqn.substr(0,i));
            eqn.erase(0,i+1);
            j++;
            i=-1;

        }
        i++;
    }
    number[j]=todouble(eqn);

    for(int w=0;w<parallel;w++){
        int d=x;
        int l=x;
        for(int t=0;t<x;t++){ //check in which position is the parallel?
            if(oper[t]==1){
                number[t]= (number[t]*number[t+1])/(number[t]+number[t+1]);
                number[t+1]=0;
                oper[t]=0;
                int p=t;
                while(number[d]!=0){  //number shifting
                    number[p+1]=number[p+2];
                    number[p+2]=0;
                    p++;
                }
                d--;
                int g=t;
                while(oper[l-1]!=0){
                    oper[g]=oper[g+1];
                    oper[g+1]=0;
                    g++;
                }
                l--;
            }
        }
    }

    double total=0;
    for(int i=0;i<=x;i++)
        total += number[i];

    cout<<"Circuit total resistance is "<<fixed<<setprecision(2)<<total<<" ohm."<<endl;
}

int main()
{
    string eqn;
    int choice=1;
    bool israndom=false;
    int numofresistor=0;
    srand(time(0));

    numofresistor=rand()%6+3;
    double number[numofresistor];
    int oper[numofresistor-1];

    cout<<"*** Welcome to Total Resistance Calculator Program ***"<<endl;
    cout<<"1. Enter circuit formula."<<endl;
    cout<<"2. Generate circuit randomly."<<endl;
    cout<<"3. Show circuit formula."<<endl;
    cout<<"4. Calculate total resistance."<<endl;

    while(choice!=4){
        cout<<"Your choice [1-4] : ";
        cin>>choice;

        if(choice==1)
            enterFormula(eqn);

        if(choice==2){
            israndom=true;
            generateRandom(numofresistor,number,oper,eqn);
        }

        if(choice==3){
            if(israndom){
                showEqnrand(number,oper,numofresistor);
            }
            else
                showEqn(eqn);
        }

        if(choice==4){
            if(israndom){
                calculateResistance(eqn);
            }
            else
                calculateResistance(eqn);
        }
    }
    return 0;
}

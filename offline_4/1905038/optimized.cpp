
#include <bits/stdc++.h>

extern ofstream outoptimize;
extern ifstream inassemble;

using namespace std;

void optimize_run();

void optimize_run()
{

    string t1, t2 , t3;

    t3 = "";
    bool flag = false;
    bool flag2 = false;

    t2 = "";

    while (getline(inassemble, t1))
    {
        outoptimize << t1 <<endl;
        if (t1 == ".CODE")
        {
            break;
        }
    }

    while (getline(inassemble, t1))
    {
        
        vector<string> tokens;

        stringstream check1(t1);

        string intermediate;

        while (getline(check1, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }

        if(tokens[0] != "\t") {
            if(t2 != "") {
                outoptimize<< t2 <<endl;
            }
            
            outoptimize << t1 << endl;
            flag = false;
            t2 = "";
           t3 = "";
           flag2 = false;
            continue;
        }

        if(tokens[1] == "MOV" && tokens[2] == "AX"){
            if(t2 != ""){
                outoptimize<< t2 <<endl;
            }

            flag2 = true;
            t3 = tokens[4];
            flag = false;
            t2 = "";
            outoptimize << t1 <<endl;
            continue;
        }
        else if( flag2 && tokens[1] == "MOV" && tokens[4]== "AX" && tokens[2] == t3){
            flag2 = false;
            t3 = "";
            flag = false;
            t2 = "";
            
            continue;
        }

        flag2 = false;
        t3 = "";

        if(tokens[1] == "PUSH" && tokens[2] == "AX"){
            if(t2 != ""){
                outoptimize<< t2 <<endl;
            }

            flag = true;
            t2 = t1;


            continue;
        }

        else if(flag && tokens[1] == "POP" && tokens[2] == "AX"){
            flag = false;
            t2 = "";
            continue;
        }
        else if(flag && tokens[1] == "POP" ){
            outoptimize<< "\t MOV "<<tokens[2]<<" , AX"<<endl;

            flag = false;
            t2 = "";
            continue;
        }

        if(t2 != "")
        outoptimize<< t2 <<endl;

        flag = false;
        t2 = "";

        if(tokens[1]== "ADD" && tokens[4]=="0"){
            continue;
        }
        else if(tokens[1]=="SUB" && tokens[4] == "0"){
            continue;
        }
        else if(tokens[1]=="IMUL" && tokens[2]=="1"){
            continue;
        }
        
        
        outoptimize<< t1 <<endl;


    }
}

#include <iostream>
#include <cstdlib> // for calling srand(), rand()
#include <ctime> // for calling time()
# include "gobang.h"
#include <fstream>
#include <sstream>
using namespace std;
void chooseboard(){
    int c;
    srand(time(NULL)); // initialize the seed for rand()
    c= rand() % 3 + 1;
    if (c==1){
    
        ifstream file("random1.txt");
        if (file.is_open()) {
            for (int i = 0; i < 15; ++i) {
                string line;
            
                if ( getline(file, line)) {
                    stringstream ss(line);
                    int num;             
                    for (int j = 0; j < 15; ++j) {
                        ss >> num;
                        Board[i][j] = num;
                    }
                }
            } 
            // 关闭文件
            file.close();
        }
    }
    if (c==2){
        ifstream file("random2.txt");
        if (file.is_open()) {
            for (int i = 0; i < 15; ++i) {
                string line;
            
                if ( getline(file, line)) {
                    stringstream ss(line);
                    int num;             
                    for (int j = 0; j < 15; ++j) {
                        ss >> num;
                        Board[i][j] = num;
                    }
                }
            } 
            // 关闭文件
            file.close();
        }
    }

    
    if (c==3){
        ifstream file("random2.txt");
        if (file.is_open()) {
            for (int i = 0; i < 15; ++i) {
                string line;
            
                if ( getline(file, line)) {
                    stringstream ss(line);
                    int num;             
                    for (int j = 0; j < 15; ++j) {
                        ss >> num;
                        Board[i][j] = num;
                    }
                }
            } 
            // 关闭文件
            file.close();
        }
    }

}
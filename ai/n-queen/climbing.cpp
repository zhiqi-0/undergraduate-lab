// solving N Queen problem (m pair attacks each other)
// using annealing alg
// author: Zhiqi Lin

#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <vector>
#include <cstdlib>

class Utility{
 private:
    static clock_t begin;
    static clock_t finish;
 public:
    static void TimeStart(){
        begin = clock();
    }
    static double TimeEnd(){
        finish = clock();
        return (double)(finish - begin) / CLOCKS_PER_SEC;
    }
    static void ReadData(int& n, int& m){
        std::ifstream inputfile("input.txt");
        inputfile >> n;
        inputfile >> m;
        inputfile.close();
    }
    static void WriteData(){}
    static int RandomInt(int rangeStart, int rangeEnd){
        int rand_var = rand() % (rangeEnd - rangeStart + 1) + rangeStart;
        return rand_var;
    }
};

class NQueen{
 private:
    int attack;
    int noAttack;
    int totalQueen;
    int* location;      // location[i] denotes i-row queen's coloumn
    int value;
    std::vector<int> diag1;  // right top diag
    std::vector<int> diag2;  // left top diag
    const int threshould;

    void valueCheck(){
        // number of abs(attacked queen - attack)
        int val = 0;
        for(int i = 0; i < totalQueen - 1; ++i){
            for(int j = i + 1; j < totalQueen; ++j){
                if(location[i] == location[j] || abs(i - j) == abs(location[i] - location[j]))
                    ++val;
            }
        }
        if(val != value){
            std::cerr << "value check failed." << std::endl;
            view(totalQueen);
            exit(-1);
        }
    }
    // exchange i-th row and j-th row: keep conflicts only
    // happen in diag
    void move(int row1, int row2){
        // remove original conflict pairs
        if(diag1[row1 - location[row1] + totalQueen - 1] > 1)
            value -= diag1[row1 - location[row1] + totalQueen - 1] - 1;
        diag1[row1 - location[row1] + totalQueen - 1] -= 1;
        if(diag2[row1 + location[row1]] > 1)
            value -= diag2[row1 + location[row1]] - 1;
        diag2[row1 + location[row1]] -= 1;

        if(diag2[row2 + location[row2]] > 1)
            value -= diag2[row2 + location[row2]] - 1;
        diag2[row2 + location[row2]] -= 1;
        if(diag1[row2 - location[row2] + totalQueen - 1] > 1)
            value -= diag1[row2 - location[row2] + totalQueen - 1] - 1;
        diag1[row2 - location[row2] + totalQueen - 1] -= 1;
        // swap two row 
        std::swap<int>(location[row1], location[row2]);
        // add new conflict pairs
        diag1[row1 - location[row1] + totalQueen - 1] += 1;
        if(diag1[row1 - location[row1] + totalQueen - 1] > 1)
            value += diag1[row1 - location[row1] + totalQueen - 1] - 1;
        diag2[row1 + location[row1]] += 1;
        if(diag2[row1 + location[row1]] > 1)
            value += diag2[row1 + location[row1]] - 1;

        diag1[row2 - location[row2] + totalQueen - 1] += 1;
        if(diag1[row2 - location[row2] + totalQueen - 1] > 1)
            value += diag1[row2 - location[row2] + totalQueen - 1] - 1;
        diag2[row2 + location[row2]] += 1;
        if(diag2[row2 + location[row2]] > 1)
            value += diag2[row2 + location[row2]] - 1;
    }
 public:
    NQueen():value(0), threshould(10){
        Utility::ReadData(totalQueen, attack);
        noAttack = totalQueen - attack;
        std::vector<bool> vacancy(totalQueen);
        for(int i = 0; i < totalQueen; ++i) vacancy[i] = true;
        // set dialog
        diag1.resize(totalQueen * 2 - 1);
        diag2.resize(totalQueen * 2 - 1);
        for(int i = 0; i < 2 * totalQueen - 1; ++i){
            diag1[i] = diag2[i] = 0;
        }
        // set location
        location = new int[totalQueen];
        int col = 0, stride = 3, start = 1;
        for(int row = 0; row < totalQueen; ++row){
            if(vacancy[col]){
                vacancy[col] = false;
                location[row] = col;
                // update diag
                diag1[row - col + totalQueen - 1] += 1;
                diag2[row + col] += 1;
                // update value
                if(diag1[row - col + totalQueen - 1] > 1)
                    value += diag1[row - col + totalQueen - 1] - 1;
                if(diag2[row + col] > 1)
                    value += diag2[row + col] - 1;
                col += stride;
                if(col >= totalQueen){
                    col = start;
                    ++start;
                }
            }
            else{
                while(!vacancy[col]){
                    col++;
                    if(col >= totalQueen){
                        col = start;
                        ++start;
                        --row;
                    }
                }
            }
        }
        
    }
    ~NQueen(){
        delete[] location;
    }
    void Anneal(){
        std::cout << "init value: " << value << std::endl;
        int step = 1;
        while(value != attack){
            int bestRow1 = 0, bestRow2 = 0;
            int delta = -1;
            int oldVal = value;
            // random sampling
            for(int sample = 0; sample < threshould; ++sample){
                int randomRow1 = Utility::RandomInt(0, totalQueen - 1);
                int randomRow2;
                while(true){
                    randomRow2 = Utility::RandomInt(0, totalQueen - 1);
                    if(randomRow2 != randomRow1) break;
                }
                move(randomRow1, randomRow2);
                // if value < attack then greedy climbing down until value > attack
                if(oldVal < attack){
                    if(value > attack) break;
                    else if(oldVal > value)
                        move(randomRow2, randomRow1);
                    break;
                }
                // climbing
                else{
                    if(value >= attack && oldVal - value > delta){
                        bestRow1 = randomRow1;
                        bestRow2 = randomRow2;
                        delta = oldVal - value;
                    }
                    move(randomRow2, randomRow1);
                }
            }
            if(delta != -1){
                // delta == -1 may have two situation:
                // one for oldVal < attack: this will be avoided by greedy climbing up
                // the other for a local maxium situation: this is not solved.
                move(bestRow1, bestRow2);
            }
        }
        //valueCheck();
    }
    void view(int n){
        n = n > totalQueen ? totalQueen : n;
        for(int row = 0; row < n; ++row){
            for(int j = 0; j < totalQueen; ++j){
                if(j != location[row])
                    std::cout << 0 << " ";
                else
                    std::cout << 1 << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "value: " << value << std::endl;
    }

    void writeResult(double timeSpan){
        std::ofstream resultFile("output_climb.txt");
        for(int i = 0; i < totalQueen; ++i){
            resultFile << location[i] << std::endl;
        }
        resultFile << timeSpan << std::endl;
    }
};

int main(){
    NQueen nq;
    clock_t start, finish;
    start = clock();
    nq.Anneal();
    finish = clock();
    double totaltime = (double)(finish - start) / CLOCKS_PER_SEC * 1000;
    nq.writeResult(totaltime);
    std::cout << "Timespan: " << totaltime << std::endl;
    return 0;
}
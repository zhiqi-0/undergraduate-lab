/* Solving 22 digit problem
 * Author: Zhiqi Lin
 * h(n): number of error digit
 */

#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <utility>
#include <set>
#include <ctime>

enum Action {L = 8, R = 4, U = 2, D = 1, Empty = 0};

class Utility{
public:
    static std::string readData(std::string filename){
        std::ifstream inputfile(filename);
        if(!inputfile.is_open()){
            std::cout << "Can't open file" << std::endl;
            exit(-1);
        }
        std::string status;
        short tmp;
        for(int i = 0; i < 25; ++i){
            inputfile >> tmp;
            status.push_back(char(tmp + '0'));
        }
        inputfile.close();
        return status;
    }
};

std::string target = Utility::readData("target.txt");
// hTable[1-22][current_index] = hTable[state[i] - '0'][current_index]
std::vector<std::vector<unsigned int> > hTable;

class ChessNode{
private:
    std::string status;
    std::string actionList;
    unsigned int value;

    static unsigned int h(std::string _status){
        int res = 0;
        for(int i = 0; i < 25; ++i){
            if(i != 11 && i != 13 && _status[i] != '0'){
                res += hTable[_status[i] - '0'][i];
            }
        }
        return res;
    }
public:
    static void initTable(){
        hTable.resize(23);
        for(int i = 1; i < 23; ++i){
            hTable[i].resize(25);
            // find 'i' in target's position
            int index = target.find(char(i + '0'));
            int row = index / 5;
            int col = index % 5;
            // set distance
            for(int k = 0; k < 5; ++k){
                for(int j = 0; j < 5; ++j){
                    hTable[i][k * 5 + j] = abs(k - row) + abs(j - col);
                    if(row <= 2 && k >= 2 && abs(col - j) > 1){
                        if(abs(col - j) > 1 && abs(col - j) < 4)
                            hTable[i][k * 5 + j] -= 1;
                        else if(abs(col - j) == 4)
                            hTable[i][k * 5 + j] -= 2;
                    }
                    else if(row >= 2 && k <= 2 && abs(col - j) > 1){
                        if(abs(col - j) > 1 && abs(col - j) < 4)
                            hTable[i][k * 5 + j] -= 1;
                        else if(abs(col - j) == 4)
                            hTable[i][k * 5 + j] -= 2;
                    }
                }
            }
        }
    }

    ChessNode(std::string _status, std::string _actionList, unsigned int _value = 0):
            status(_status), actionList(_actionList), value(_value) {}
    ~ChessNode() {}
    
    unsigned int setValue(){
        value = actionList.size() + h(status);
        return value;
    }
    std::string getStatus() {return status;}
    std::string getPath() {return actionList;}
    unsigned int getValue() {return value;}
    
    /* nextMove: get action space
     * 1111 = L || R || U || D
     */
    int moveSpace(){
        int index = status.find('0');
        int res = 0;
        res = (index % 5 == 0) ? res << 1 : (res << 1) + 1;       // L
        res = (index % 5 == 4) ? res << 1 : (res << 1) + 1;       // R
        res = (index < 5 || index == 16 || index == 18) ? res << 1 : (res << 1) + 1; // U
        res = (index >= 20 || index == 6 || index == 8) ? res << 1 : (res << 1) + 1; // D
        if(actionList.size() > 0){
            switch(actionList[actionList.size() - 1]){
                case 'L': res = res - 4; break;
                case 'R': res = res - 8; break;
                case 'U': res = res - 1; break;
                case 'D': res = res - 2; break;
            }
        }
        return res;
    }
    bool move(enum Action a){
        int index = status.find('0');
        int ofs = 0;
        switch(a){
            case D: std::swap(status[index], status[index + 5]); actionList += "D";
                ofs = 5; break;
            case U: std::swap(status[index], status[index - 5]); actionList += "U";
                ofs = -5; break;
            case L: if(index == 12 || index == 14){
                std::swap(status[index], status[index - 2]);
                ofs = -2;
            }
            else{
                std::swap(status[index], status[index - 1]);
                ofs = -1;
            }
                actionList += "L"; break;
            case R: if(index == 10 || index == 12){
                std::swap(status[index], status[index + 2]);
                ofs = 2;
            }
            else{
                std::swap(status[index], status[index + 1]);
                ofs = 1;
            }
                actionList += "R"; break;
            default: return false;
        }
        // change value
        value -= hTable[status[index] - '0'][index + ofs];
        value += hTable[status[index] - '0'][index];
        value += 1;         // for g(n)
        return true;
    }
    
    void moveBack(){
        if(actionList.size() == 0) return;
        value -= 2;
        Action back = Empty;
        switch(actionList[actionList.size() - 1]){
            case 'U': back = D; break;
            case 'D': back = U; break;
            case 'L': back = R; break;
            case 'R': back = L; break;
        }
        move(back);
        actionList.erase(actionList.size() - 2, 2);
    }
};

class ChessBoard{
private:
    struct QueueNode{
        std::string status;
        std::string path;
        unsigned int value;
        friend inline bool operator< (const QueueNode& node1, const QueueNode& node2){
            return node1.value > node2.value;
        }
    };
    std::priority_queue<QueueNode> fringe;
    std::string solution;
    ChessNode init;
    
public:
    ChessBoard(std::string filename):
            init(ChessNode(Utility::readData(filename), "")),
            solution(""){
        ChessNode::initTable();
        QueueNode initNode = {init.getStatus(), "", init.setValue()};
        fringe.push(initNode);
    }
    
    void AStar(){
        if(init.getValue() == 0) return;
        while(true){
            QueueNode node = fringe.top();
            fringe.pop();
            init = ChessNode(node.status, node.path, node.value);
            int nextMove = init.moveSpace();
            int moveType = 0;
            while(nextMove != 0){
                int step = nextMove % 2;
                if(init.move(Action(step << moveType))){
                    unsigned int val = init.getValue();
                    if(val - init.getPath().size() == 0){
                        solution = init.getPath();
                        return;
                    }
                    QueueNode addNode = {init.getStatus(), init.getPath(), val};
                    fringe.push(addNode);
                    init.moveBack();
                }
                nextMove = nextMove >> 1;
                ++moveType;
            }
        }
    }
    
    void run(){
        clock_t start, finish;
        start = clock();
        AStar();
        finish = clock();
        double totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
        // write result to output
        std::ofstream outputfile("output_Ah2.txt");
        outputfile << totaltime << std::endl;
        outputfile << solution << std::endl;
        outputfile << solution.size() << std::endl;
    }
};

int main(){
    ChessBoard chessboard("input.txt");
    chessboard.run();
    return 0;
}


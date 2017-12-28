#include<iostream>
#include<list>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

typedef struct LogicUnit{
    bool no;
    int xi;
}LogicUnit;

typedef list<LogicUnit> Disjunct;

typedef list<Disjunct> LogicSet;

void setprint(LogicSet &logicset){
    LogicSet::iterator ls;
    Disjunct::iterator ds;
    for(ls = logicset.begin(); ls != logicset.end(); ++ls){
        if(ls != logicset.begin())
            cout << " ^ ";
        cout << '(';
        for(ds = ls -> begin(); ds != ls -> end(); ++ds){
            if(ds != ls -> begin())
                cout << " v ";
            if(ds -> no)
                cout << "~";
            cout << "x" << ds -> xi;
        }
        cout << ')';
    }
    cout << endl;
}

void DisjunctPrint(Disjunct &a){
    Disjunct::iterator ds;
    for(ds = a.begin(); ds != a.end(); ++ds){
        if(ds != a.begin())
            cout << " v ";
        if(ds -> no)
            cout << "~";
        cout << "x" << ds -> xi;
    }
    cout << endl;
}


bool _DisCompare(Disjunct &a, Disjunct &b){
    return int(a.size()) < int(b.size());
}

bool _LogicUnitCompare(LogicUnit &a, LogicUnit &b){
    if(a.xi < b.xi)
        return true;
    else if(a.xi > b.xi)
        return false;
    else if(a.no == true)
        return true;
    else
        return false;
}

bool _DisEqual(Disjunct &a, Disjunct &b){
    Disjunct::iterator da, db;
    a.sort(_LogicUnitCompare);
    b.sort(_LogicUnitCompare);
    bool same = true;
    for(da = a.begin(), db = b.begin(); da != a.end() && db != b.end(); ++da, ++db){
        if(da -> no != db -> no || da -> xi != db -> xi){
            same = false; break;
        }
    }
    if(!same || da != a.end() || db != b.end())
        return false;
    else
        return true;
}

bool DisjunctSimplify(Disjunct &a){         // return true: ok. return false: should be delete (1)
    a.sort(_LogicUnitCompare);
    Disjunct::iterator d1,d2;
    d1 = a.end();
    for(d2 = a.begin(); d2 != a.end(); ++d2){
        if(d1 == a.end()){
            d1 = d2; continue;
        }
        if(d1 -> xi == d2 -> xi){
            if(d1 -> no != d2 -> no)
                return false;
            else{
                a.erase(d1);
                d1 = d2;
            }
        }
        d1 = d2;
    }
    return true;
}

bool FindDisjunct(Disjunct &a, LogicSet &logicset){  // disjunct request sort already
    LogicSet::iterator ls;
    bool findd = false;
    for(ls = logicset.begin(); ls != logicset.end(); ++ls){
        if(_DisEqual(a, *ls))
            findd = true;
    }
    return findd;
}

void logicsort(LogicSet &logicset){
    logicset.sort(_DisCompare);
    LogicSet::iterator ls;
    Disjunct::iterator ds1,ds2;
    for(ls = logicset.begin(); ls != logicset.end(); ++ls){
        ls -> sort(_LogicUnitCompare);
    }
}

bool logicmerge(LogicSet::iterator ls1, LogicSet::iterator ls2,
                LogicSet &logicset, bool &KO){
    Disjunct tmp1 = *ls1, tmp2 = *ls2;
    Disjunct::iterator ds1, ds2, temp1, temp2;
    bool res = false, print = false;
    
    for(ds1 = tmp1.begin(); ds1 != tmp1.end(); ++ds1){
        for(ds2 = tmp2.begin(); ds2 != tmp2.end(); ++ds2){
            if(ds1 -> xi == ds2 -> xi && ds1 -> no != ds2 ->no){
                temp1 = ds1; temp2 = ds2;
                --ds1; --ds2;
                tmp1.erase(temp1); tmp2.erase(temp2);
                res = true;
            }
        }
    }
    
    if(res){
        tmp1.merge(tmp2, _LogicUnitCompare);

        if(DisjunctSimplify(tmp1)){
            if(!FindDisjunct(tmp1, logicset)){
                print = true;
                logicset.push_back(tmp1);
                if(tmp1.size() == 0)
                    KO = true;
                else
                    KO = false;
            }
            
        }
    }
    return print;
}

bool resolution(LogicSet &logicset){
    LogicSet::iterator ls1, ls2;
    Disjunct::iterator ds1, ds2;
    bool res = true;
    bool KO = false;
    
    cout << "Initial begin:\n";
    logicsort(logicset);
    setprint(logicset);
    
    /* if contain disjunct such like x2 v ~x2 then ok */
    for(ls1 = logicset.begin(); ls1 != logicset.end(); ++ls1){
        if(!DisjunctSimplify(*ls1)){
            logicset.erase(ls1);
            logicset.push_back(Disjunct());
            setprint(logicset);
            cout << "Success in Prove\n";
            return true;
        }
    }
    
    while(res){
        res = false;
        for(ls1 = logicset.begin(); ls1 != logicset.end(); ++ls1){
            ls2 = ls1; ++ls2;
            for(;ls2 != logicset.end(); ++ls2){
                
                /* test begin */
                //cout << "current handle:\n";
                //DisjunctPrint(*ls1); DisjunctPrint(*ls2);
                /* test end */
                

                if(logicmerge(ls1, ls2, logicset, KO)){
                    setprint(logicset);
                    res = true;
                }
                if(KO){
                    cout << "Success in Prove\n";
                    return true;
                }
                
                /* test begin */
                //cout << "after merge state:\n";
                //setprint(logicset);
                /* test end */
            }
        }
        logicsort(logicset);
    }
    cout << "Can't be Proved.\n";
    return false;
    
}

void LogicConvert(int degree, string &s, LogicSet &logicset){ //只适用于合取范式的转化
    vector<LogicUnit> logicbank;
    logicbank.resize((degree + 1)*2);
    for(int i = 1; i <= degree*2; i += 2){
        logicbank.at(i) = LogicUnit{false, (i + 1)/2};
        logicbank.at(i+1) = LogicUnit{true, (i + 1)/2};
    }
    
    int len = int(s.length());
    int i,j;
    Disjunct tmp;
    for(i = 0; i < len; ++i){
        if(s[i] == 'x'){
            for(j = i + 1; j < len && (s[j] < '0' || s[j] > '9'); ++j);
            if(int(s[j] - '0') <= degree){
                tmp.push_back(logicbank.at(2*int(s[j] - '0') - 1));
                i = j;
            }
            // not debug
        }
        else if(s[i] == '~'){
            for(j = i + 1;j < len && (s[j] < '0' || s[j] > '9'); ++j);
            if(int(s[j] - '0') <= degree){
                tmp.push_back(logicbank.at(2*int(s[j] - '0')));
                i = j;
            }
            // not debug
        }
        else if(s[i] == '^'){
            logicset.push_back(tmp);
            tmp.clear();
        }
    }
    logicset.push_back(tmp);
}

int main(){
    LogicSet logicset; int degree; string s;
    cout << "enter degree: "; cin >> degree; cin.get();
    cout << "enter string: \n";
    getline(cin,s);
    LogicConvert(degree, s, logicset);
    resolution(logicset);
    return 0;
    
}


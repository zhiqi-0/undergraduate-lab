#include<iostream>
#include<cstdlib>
#include<unordered_map>
#include<string>
#include<tuple>
#include<vector>
#include<sstream>
#include<iterator>
#include<algorithm>
#include "lzq.h"

enum LockType {S = 0, X, U};

class DBLock{
 private:
    // [object, lock type]
    std::unordered_map<std::string, LockType> _lockTable;
    // [object, <transactionID, lock type>]
    std::unordered_map<std::string, std::vector<std::tuple<std::string, LockType> > > _lockWait;
    // transactionID [occupied object]
    std::unordered_map<std::string, std::vector<std::string> > _occupy;

    void _getCommand();
    void _handleStart(std::string transactionID);
    void _handleEnd(std::string transactionID);
    void _handleUnlock(std::string transactionID, const std::string& object);
    void _handleLock(std::string transactionID, const std::string& object, LockType lockType);
    void _show();

 public:
    // default initialize
    DBLock();
    // initialize terminal
    void init();
    
};
#include "dblock.h"

DBLock::DBLock(){
    _lockTable.clear();
    _lockWait.clear();
}

void DBLock::init(){
    std::cout << "Database Lock Simulator v0.01" << std::endl;
    while(true){
        std::cerr << "> ";
        _getCommand();
    }
}

void DBLock::_getCommand(){
    std::string command;
    std::getline(std::cin, command);
    //std::cout << "get command: " << command << std::endl;
    if(command == "") return;
    std::vector<std::string> keys = lzq::String::split(command, ' ');
    if(keys.size() == 0) return;
    if(keys[0] == "exit") exit(0);
    if(keys.size() != 2 && keys.size() != 3){
        std::cout << "Expected Instruction: <request type> <transaction ID> <object>"
                  << std::endl;
        return;
    }
    // handle request type -- start
    if(keys[0] == "start"){
        if(keys.size() == 3){
            std::cout << "Unkown instruction for [start]: " << keys[2] << std::endl;
            return;
        }
        _handleStart(keys[1]);
    }
    // handle request type -- unlock
    else if(keys[0] == "end"){
        if(keys.size() == 3){
            std::cout << "Unkown instruction for [end]: " << keys[2] << std::endl;
            return;
        }
        _handleEnd(keys[1]);
    }
    // handle request type -- SLock
    else if(keys[0] == "slock"){
        if(keys.size() != 3){
            std::cout << "Expected usage for Lock instruction: <?lock> <transaction ID> <object>\n";
            return;
        }
        _handleLock(keys[1], keys[2], LockType::S);
    }
    // handle request type -- XLock
    else if(keys[0] == "xlock"){
        if(keys.size() != 3){
            std::cout << "Expected usage for Lock instruction: <?lock> <transaction ID> <object>\n";
            return;
        }
        _handleLock(keys[1], keys[2], LockType::X);
    }
    // handle request type -- ULock
    else if(keys[0] == "ulock"){
        if(keys.size() != 3){
            std::cout << "Expected usage for Lock instruction: <?lock> <transaction ID> <object>\n";
            return;
        }
        _handleLock(keys[1], keys[2], LockType::U);
    }
    else if(keys[0] == "unlock"){
        if(keys.size() != 3){
             std::cout << "Expected usage for unlock instruction: unlock <transaction ID> <object>\n";
            return;
        }
        _handleUnlock(keys[1], keys[2]);
    }
    // show table
    else if(keys[0] == "show" && keys[1] == "table"){
        _show();
    }
    else{
        std::cout << "Unknown Instruction Type. Please re-check." << std::endl;
    }
}

void DBLock::_handleStart(std::string transactionID){
    if(_occupy.find(transactionID) != _occupy.end()){
        std::cout << "Transaction " << transactionID << " has already started. Create Failed." << std::endl;
        return;
    }
    _occupy[transactionID] = std::vector<std::string>();
    std::cout << "Transaction " << transactionID << " is now starting..." << std::endl;
    return;
}

void DBLock::_handleEnd(std::string transactionID){
    auto occIt = _occupy.find(transactionID);
    if(occIt == _occupy.end()){
        std::cout << "Transaction " << transactionID << " doesn't exist" << std::endl;
        return;
    }
    // unlock occupied obj
    std::vector<std::string> objs = occIt->second;
    for(int i = 0; i < objs.size(); ++i){
        _handleUnlock(transactionID, objs[i]);
    }

    // remove occupy list
    _occupy.erase(occIt);

    // remove wait list
    for(auto& item : _lockWait){
        auto objs = item.second;
        for(int i = 0; i < objs.size(); ++i){
            if(std::get<0>(objs[i]) == transactionID){
                objs.erase(objs.begin() + i);
                --i;
            }
        }
        if(objs.size() == 0)
            _lockWait.erase(item.first);
        else
            _lockWait[item.first] = objs;
    }
    
    std::cout << "Transaction " << transactionID << " is now closed" << std::endl;
    return;
}

void DBLock::_handleUnlock(std::string transactionID, const std::string& object){
    std::string typeString[3] = {"S-Lock", "X-Lock", "U-Lock"};
    // remove _occupy element
    auto occIt = _occupy.find(transactionID);
    if(occIt == _occupy.end()){
        std::cout << "Transaction " << transactionID << " doesn't exist" << std::endl;
        return;
    }
    std::vector<std::string> objs = occIt->second;
    auto pos = std::find(objs.begin(), objs.end(), object);
    objs.erase(pos);
    _occupy[transactionID] = objs;

    // remove _lockTable key
    auto tableIt = _lockTable.find(object);
    if(tableIt == _lockTable.end()){
        std::cout << object << " doesn't have any locks\n";
        return;
    }
    LockType type = tableIt->second;
    _lockTable.erase(object);
    std::cout << "Release " << typeString[type] << " on " << occIt->first << std::endl;

    // check waiting list
    auto waitIt = _lockWait.find(object);
    if(waitIt != _lockWait.end()){
        // get waiting locks info
        std::string waitTransID = std::get<0>(waitIt->second[0]);
        LockType waitLockType = std::get<1>(waitIt->second[0]);
        // add locks
        _lockTable[object] = waitLockType;
        std::cout << typeString[waitLockType] << " " + object + " : Lock granted to " 
                  << waitTransID << std::endl;
        // add occupy
        _occupy[waitTransID].push_back(object);
        // remove
        _lockWait[object].erase(_lockWait[object].begin());
        if(_lockWait[object].size() == 0)
            _lockWait.erase(object);
    }

    return;
}

void DBLock::_handleLock(std::string transactionID, const std::string& object, LockType lockType){
    std::string typeString[3] = {"S-Lock", "X-Lock", "U-Lock"};
    auto occupyIt = _occupy.find(transactionID);
    if(occupyIt == _occupy.end()){
        std::cout << "No match transaction ID is working. Lock Failed\n";
        return;
    }
    // check whether object is locked
    auto tableIt = _lockTable.find(object);
    if(tableIt == _lockTable.end()){
        _lockTable[object] = lockType;
        std::cout << typeString[lockType] << " " + transactionID << " " + object
                  << " : Lock granted" << std::endl;
        // add to occupy
        if(occupyIt == _occupy.end())
            _occupy[transactionID] = std::vector<std::string>();
        _occupy[transactionID].push_back(object);
        return;
    }
    // check whether the transaction already has this lock
    auto pos = std::find(occupyIt->second.begin(), occupyIt->second.end(), object);
    if(pos != occupyIt->second.end() && lockType == tableIt->second){
        std::cout << "Already has a " << typeString[lockType] << " on transaction ID "
                  << transactionID << ". Lock Failed\n";
        return;
    }
    // if X-Lock: check whether a S-Lock is held by this transaction
    if(lockType == LockType::X){
        bool isSLock = tableIt->second == LockType::S;
        bool thisTransaction = false;
        auto objs = occupyIt->second;
        for(int i = 0; i < objs.size(); ++i){
            if(objs[i] == object){
                thisTransaction = true;
                break;
            }
        }
        if(isSLock && thisTransaction){
            _lockTable[object] = lockType;
            std::cout << "Upgrade to X-Lock granted\n";
            return;
        }
    }
    // add to wait list
    auto waitIt = _lockWait.find(object);
    if(waitIt == _lockWait.end()){
        _lockWait[object] = std::vector<std::tuple<std::string, LockType> >();
        _lockWait[object].push_back(std::make_tuple(transactionID, lockType));
    }
    // check wheter wait list have S lock on same transaction: S->X
    else if(lockType == LockType::X){
        auto waitList = _lockWait[object];
        for(int i = 0; i < waitList.size(); ++i){
            if(std::get<0>(waitList[i]) == transactionID && std::get<1>(waitList[i]) == LockType::S){
                waitList.erase(waitList.begin() + i);
                break;
            }
        }
        waitList.push_back(std::make_tuple(transactionID, lockType));
        _lockWait[object] = waitList;
    }
    std::cout << typeString[lockType] << " " + transactionID << " " + object
              << " : Wait for lock" << std::endl;
    return;
}

void DBLock::_show(){
    std::string typeString[3] = {"S-Lock", "X-Lock", "U-Lock"};
    std::cout << "================= Lock Table ===============" << std::endl;
    for(auto& item : _lockTable){
        std::cout << "object: " << item.first << "\tLock Type: " << typeString[item.second]
                  << std::endl;
    }
    std::cout << "================= Wait List ===============" << std::endl;
    for(auto& item : _lockWait){
        std::cout << "object: " << item.first << "\twait list: ";
        auto waitLocks = item.second;
        for(int i = 0; i < waitLocks.size(); ++i){
            std::cout << typeString[std::get<1>(waitLocks[i])] 
                      << "(" << std::get<0>(waitLocks[i]) << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << "================= Occupy List ===============" << std::endl;
    for(auto& item : _occupy){
        std::cout << "transaction ID: " << item.first << "\tobject: ";
        auto occcupys = item.second;
        for(int i = 0; i < occcupys.size(); ++i){
            std::cout << occcupys[i] << " ";
        }
        std::cout << std::endl;
    }
    return;
}


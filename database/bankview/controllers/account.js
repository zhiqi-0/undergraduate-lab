const Account = require('../models/account');
const customer = require('../models/customer');
const Sequelize = require('sequelize');
const fs = require('fs');
const path = require('path');

function deleteEmpty(obj){
    Object.keys(obj).forEach(function(key) {
        if(obj[key] === '' || obj[key] == null){
            delete obj[key];
        }
    });
}

var post_account = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/account.html');
    var accountExist = {
        账户号: ctx.request.body.existAccNum,
        余额: ctx.request.body.existBalance,
        开户日期: ctx.request.body.existOpenDate,
        最近访问日期: ctx.request.body.existLastVisitDate
    };
    var accountNew = {
        账户号: ctx.request.body.newAccNum,
        余额: ctx.request.body.newBalance,
        开户日期: ctx.request.body.newOpenDate,
        最近访问日期: ctx.request.body.newLastVisitDate
    };
    var savingAccountExist = {
        账户号: ctx.request.body.existAccNum,
        余额: ctx.request.body.existBalance,
        开户日期: ctx.request.body.existOpenDate,
        最近访问日期: ctx.request.body.existLastVisitDate,
        利率: ctx.request.body.existInterest,
        货币类型: ctx.request.body.exitCurrType
    };
    var savingAccountNew = {
        账户号: ctx.request.body.newAccNum,
        余额: ctx.request.body.newBalance,
        开户日期: ctx.request.body.newOpenDate,
        最近访问日期: ctx.request.body.newLastVisitDate,
        利率: ctx.request.body.newInterest,
        货币类型: ctx.request.body.newCurrType
    };
    var creditAccountExist = {
        账户号: ctx.request.body.existAccNum,
        余额: ctx.request.body.existBalance,
        开户日期: ctx.request.body.existOpenDate,
        最近访问日期: ctx.request.body.existLastVisitDate,
        透支额: ctx.request.body.existOverdraft
    };
    var creditAccountNew = {
        账户号: ctx.request.body.newAccNum,
        余额: ctx.request.body.newBalance,
        开户日期: ctx.request.body.newOpenDate,
        最近访问日期: ctx.request.body.newLastVisitDate,
        透支额: ctx.request.body.newOverdraft
    };
    var openAccountNew = {
        身份证: ctx.request.body.newCusID,
        账户号: ctx.request.body.newAccNum,
        开户行: ctx.request.body.newBranchName,
        账户类型: ctx.request.body.newCardType
    };
    var option = ctx.request.body.option || 'Search';
    var existType = ctx.request.body.existCardType;
    var newType = ctx.request.body.newCardType;
    deleteEmpty(accountExist);
    deleteEmpty(accountNew);
    deleteEmpty(savingAccountExist);
    deleteEmpty(savingAccountNew);
    deleteEmpty(creditAccountExist);
    deleteEmpty(creditAccountNew);
    deleteEmpty(openAccountNew);
    var submitRes = 'submit success';
    var res = 0;
    if(option === 'Search'){
        var creditRes = [], savingRes = [], accounts = [];
        if(existType === 'Credit' || existType === 'All'){
            creditRes = await Account.creditAccount.findAll({
                where: creditAccountExist
            });
            accounts = accounts.concat(creditRes);
        }
        if(existType === 'Saving' || existType === 'All'){
            savingRes = await Account.savingAccount.findAll({
                where: savingAccountExist
            });
            accounts = accounts.concat(savingRes);
        }
    }
    else if(option === 'Create'){
        var checkExist = Account.openAccount.findAll({
            where:{
                身份证: ctx.request.body.newCusID,
                开户行: ctx.request.body.newBranchName,
                账户类型: newType
            }
        });
        if(!checkExist.length){
            try{
                await Account.account.create(accountNew);
                await Account.openAccount.create(openAccountNew);
                if(newType === 'Credit'){
                    await Account.creditAccount.create(creditAccountNew);
                    var accounts = [creditAccountNew];
                }
                else{
                    await Account.savingAccount.create(savingAccountNew);
                    var accounts = [savingAccountNew];
                }
            }catch(e){
                console.log('Account Customer ID not exist. Create Failed.');
                submitRes = 'Account Customer ID not exist. Create Failed.';
                accounts = [];
                res = 1;
            }
        }
        else{
            console.log("One Branch No more than 1 card per type. Create Failed");
            submitRes = 'Account Customer ID not exist. Create Failed.';
            accounts = [];
        }
    }
    else if(option === 'Delete'){
        try{
            // delete open account table
            var openAccounts = await Account.openAccount.findAll({
                where: {
                    账户号: ctx.request.body.existAccNum
                }
            });
            for(let opacc of openAccounts){
                await opacc.destroy();
            }
            // delete credit/saving account table
            if(existType === 'Credit'){
                var accounts = await Account.creditAccount.findAll({
                    where: creditAccountExist
                });
            }
            else{
                var accounts = await Account.savingAccount.findAll({
                    where: savingAccountExist
                });
            }
            for(let acc of accounts){
                await acc.destroy();
            }
            // delete account table
            var basicAccounts = await Account.account.findAll({
                where: accountExist
            });
            for(let bacc of basicAccounts){
                await bacc.destroy();
            }
        }catch(e){
            console.log('Account Foreign Key Error. Delete Failed.');
            submitRes = 'Account Foreign Key Error. Delete Failed.';
            accounts = [];
            res = 1;
        }
    }
    else if(option === 'Update'){
        try{
            // update account info
            var basicAccounts = await Account.account.findAll({
                where: accountNew
            });
            for(let bacc of basicAccounts){
                Object.keys(accountNew).forEach(function(key){
                    if(key != '账户号'){
                        bacc[key] = accountNew[key];
                    }
                })
                await bacc.save();
            }
            // update specific account info
            if(existType === 'Credit'){
                var accounts = await Account.creditAccount.findAll({
                    where: creditAccountExist
                });
                for(let acc of accounts){
                    Object.keys(creditAccountNew).forEach(function(key){
                        if(key != '账户号'){
                            acc[key] = creditAccountNew[key];
                        }
                    })
                    await acc.save();
                }
            }
            else if(existType === 'Saving'){
                var accounts = await Account.savingAccount.findAll({
                    where: savingAccountExist
                });
                for(let acc of accounts){
                    Object.keys(savingAccountNew).forEach(function(key){
                        if(key != '账户号'){
                            acc[key] = savingAccountNew[key];
                        }
                    })
                    await acc.save();
                }
            }
        }catch(e){
            console.log('Account Foreign Key Error. Create Failed.');
            submitRes = 'Account Foreign Key Error. Create Failed.';
            accounts = [];
            res = 1;
        }
    }
    ctx.render(filepath, {accounts: accounts, res: res, submitRes: submitRes});
};

module.exports = {
    'POST /account': post_account
}
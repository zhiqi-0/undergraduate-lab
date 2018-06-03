const Account = require('../models/account');
const Sequelize = require('sequelize');
const fs = require('fs');
const path = require('path');

function deleteEmpty(obj){
    Object.keys(obj).forEach(function(key) {
        if(obj[key] === ''){
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
    var option = ctx.request.body.option || 'Search';
    deleteEmpty(accountExist);
    deleteEmpty(accountNew);
    deleteEmpty(savingAccountExist);
    deleteEmpty(savingAccountNew);
    deleteEmpty(creditAccountExist);
    deleteEmpty(creditAccountNew);
    if(option === 'Search'){
        var accounts = await Account.account.findAll({
            where: accountExist
        });
    }
    else if(option === 'Create'){
        var accounts = await Account.account.create(accountNew);
        accounts = [accountNew];
    }
    else if(option === 'Delete'){
        var accounts = await Account.account.findAll({
            where: accountExist
        });
        for(let acc of accounts){
            await acc.destroy();
        }
    }
    else if(option === 'Update'){
        var accounts = await Account.account.findAll({
            where: accountExist
        });
        for(let acc of accounts){
            Object.keys(accountNew).forEach(function(key){
                acc[key] = accountNew[key];
            });
            await acc.save();
        }
    }
    ctx.render(filepath, {accounts: accounts});
};

module.exports = {
    'POST /account': post_account
}
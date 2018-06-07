const Loan = require('../models/loan');
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

var post_loan = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/loan.html');
    var loanExist = {
        贷款号: ctx.request.body.existLoanID,
        支行名:     ctx.request.body.existBranchName,
        贷款金额:   ctx.request.body.existMoney,
        总共支付次数: ctx.request.body.existPaymentTime
    };
    var loanNew = {
        贷款号:        ctx.request.body.newLoanID,
        支行名:        ctx.request.body.newBranchName,
        贷款金额:      ctx.request.body.newMoney,
        总共支付次数:   ctx.request.body.newPaymentTime
    };
    option = ctx.request.body.option;
    var submitRes = 'submit success';
    var res = 0;
    deleteEmpty(loanExist);
    deleteEmpty(loanNew);
    if(option === 'Search'){
        var loans = await Loan.loan.findAll({
            where: loanExist
        });
        for(l of loans){
            var finishState = '未开始';
            var pays = await Loan.payment.findAll({
                where: {
                    支付序号: 1,
                    贷款号: l.贷款号
                }
            });
            if(pays.length == 0){
                finishState = '未开始';
            }
            else{
                pays = await Loan.payment.findAll({
                    where: {
                        支付序号: l.总共支付次数,
                        贷款号: l.贷款号
                    }
                });
                if(pays.length != 0)
                    finishState = '已完成';
                else
                    finishState = '进行中';
            }
            l.完成情况 = finishState;
        }
    }
    else if(option === 'Create'){
        try{
            var loans = await Loan.loan.create(loanNew);
            loans = [loanNew];
        }catch(e){
            console.log('Loan: Unknown Branch Name. Create Failed');
            submitRes = 'Loan: Unknown Branch Name. Create Failed';
            loans = [];
            res = 1;
        }
    }
    else if(option === 'Delete'){
        var loans = await Loan.loan.findAll({
            where: loanExist
        });
        for(let l of loans){
            var pays = await Loan.payment.findAll({
                where: {
                    支付序号: l.总共支付次数,
                    贷款号: l.贷款号
                }
            });
            if(pays.length != 0){
                pays = await Loan.payment.findAll({
                    where: {
                        贷款号: l.贷款号
                    }
                });
                for(p of pays)
                    p.destroy();
            }
            try{
                await l.destroy();
                l.完成情况 = '完成已删除';
            }catch(e){
                console.log('Loan: Foreign Key Error. Delete Failed');
                submitRes = 'Loan: Loan is Under Processing. Delete Failed';
                loans = [];
                res = 1;
            }
        }
    }
    /*else if(option === 'Update'){
        var loans = await Loan.loan.findAll({
            where: loanExist
        });
        for(let l of loans){
            Object.keys(loanNew).forEach(function(key){
                l[key] = loanNew[key];
            });
            try{
                await l.save();
            }catch(e){
                console.log('Loan: Foreign Key Error. Update Failed');
                submitRes = 'Loan: Foreign Key Error. Update Failed';
                loans = [];
                res = 1;
            }
        }
    }*/
    ctx.render(filepath, {loans: loans, res: res, submitRes: submitRes});
};

module.exports = {
    'POST /loan': post_loan
};
const loan = require('../models/loan');
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
        var loans = await loan.findAll({
            where: loanExist
        });
    }
    else if(option === 'Create'){
        try{
            var loans = await loan.create(loanNew);
            loans = [loanNew];
        }catch(e){
            console.log('Loan: Unknown Branch Name. Create Failed');
            submitRes = 'Loan: Unknown Branch Name. Create Failed';
            loans = [];
            res = 1;
        }
    }
    else if(option === 'Delete'){
        var loans = await loan.findAll({
            where: loanExist
        });
        for(let l of loans){
            try{
                l.destroy();
            }catch(e){
                console.log('Loan: Foreign Key Error. Delete Failed');
                submitRes = 'Loan: Foreign Key Error. Delete Failed';
                loans = [];
                res = 1;
            }
        }
    }
    /*else if(option === 'Update'){
        var loans = await loan.findAll({
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
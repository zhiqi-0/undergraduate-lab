const customer = require('../models/customer');
const employer = require('../models/employer');
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

var post_customer = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/customer.html');
    var employerExist = {
        身份证: ctx.request.body.newAssigneeID
    };
    var customerExist = {
        身份证: ctx.request.body.existID,
        员工_身份证: ctx.request.body.existAssigneeID,
        姓名: ctx.request.body.existName,
        家庭地址: ctx.request.body.existAddr,
        电话号码: ctx.request.body.existPhone,
        联系人姓名: ctx.request.body.existConName,
        联系人手机: ctx.request.body.existConPhone,
        联系人邮箱: ctx.request.body.existConMail,
        联系人关系: ctx.request.body.existConRelation
    };
    var customerNew = {
        身份证: ctx.request.body.newID,
        员工_身份证: ctx.request.body.newAssigneeID,
        姓名: ctx.request.body.newName,
        家庭地址: ctx.request.body.newAddr,
        电话号码: ctx.request.body.newPhone,
        联系人姓名: ctx.request.body.newConName,
        联系人手机: ctx.request.body.newConPhone,
        联系人邮箱: ctx.request.body.newConMail,
        联系人关系: ctx.request.body.newConRelation
    };
    var option = ctx.request.body.option;
    var submitRes = 'submit success';
    var res = 0;
    deleteEmpty(customerExist);
    deleteEmpty(customerNew);
    if(option === 'Search'){
        var customers = await customer.findAll({
            where: customerExist
        });
    }
    else if(option === 'Create'){
        try{
            var customers = await customer.create(customerNew);
            customers = [customerNew];
        }catch(e){
            console.log('Customer: Employer ID not exist');
            submitRes = 'Customer: Employer ID not exist';
            customers = [];
            res = 1;
        }
    }
    else if(option === 'Delete'){
        var customers = await customer.findAll({
            where: customerExist
        });
        for(let cus of customers){
            try{
                await cus.destroy();
            }catch(e){
                console.log('Customer: Foreign Key Error. Delete Failed');
                submitRes = 'Customer: Foreign Key Error. Delete Failed';
                customers = [];
                res = 1;
            }
        }
    }
    else if(option === 'Update'){
        var customers = await customer.findAll({
            where: customerExist
        });
        for(let cus of customers){
            Object.keys(customerNew).forEach(function(key){
                cus[key] = customerNew[key];
            });
            try{
                await cus.save();
            }catch(e){
                console.log('Customer: Foreign Key Error. Update Failed');
                submitRes = 'Customer: Foreign Key Error. Update Failed';
                customers = [];
                res = 1;
            }
        }
    }
    ctx.render(filepath, {customers: customers, res: res, submitRes: submitRes});
}

module.exports = {
    'POST /customer': post_customer
};
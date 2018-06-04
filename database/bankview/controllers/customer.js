const customer = require('../models/customer');
const people = require('../models/people');
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
    var peopleExist = {
        身份证: ctx.request.body.existID
    };
    var employerExist = {
        身份证: ctx.request.body.newAssigneeID
    };
    var peopleNew = {
        身份证: ctx.request.body.newID,
        姓名: ctx.request.body.newName,
        家庭地址: ctx.request.body.newAddr,
        电话号码: ctx.request.body.newPhone
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
    deleteEmpty(customerExist);
    deleteEmpty(customerNew);
    deleteEmpty(peopleNew);
    if(option === 'Search'){
        var customers = await customer.findAll({
            where: customerExist
        });
    }
    else if(option === 'Create'){
         // if people table haven't got this customer, add it
        var peoples = await people.findAll({
            where: peopleNew
        });
        if(!Object.keys(peoples).length){
            await people.create(peopleNew);
        }
        // check employer table
        var employers = await people.findAll({
            where: employerExist
        });
        if(!Object.keys(employers).length){
            console.log("employer: didn't find employer:" + ctx.request.body.newAssigneeID);
            ctx.render(filepath, {});
            return;
        }
        var customers = await customer.create(customerNew);
        customers = [customerNew];
    }
    else if(option === 'Delete'){
        var customers = await customer.findAll({
            where: customerExist
        });
        for(let cus of customers){
            await cus.destroy();
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
            await cus.save();
        }
    }
    ctx.render(filepath, {customers: customers});
}

module.exports = {
    'POST /customer': post_customer
};
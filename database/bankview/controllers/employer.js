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

var post_employer = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/employer.html');
    var peopleExist = {
        身份证: ctx.request.body.existID
    };
    var peopleNew = {
        身份证: ctx.request.body.newID,
        姓名: ctx.request.body.newName,
        家庭地址: ctx.request.body.newAddr,
        电话号码: ctx.request.body.newPhone
    };
    var employerExist = {
        身份证: ctx.request.body.existID,
        部门号: ctx.request.body.existDepartNum,
        姓名: ctx.request.body.existName,
        家庭地址: ctx.request.body.existAddr,
        电话号码: ctx.request.body.existPhone,
        开始工作日期: ctx.request.body.existWorkTime
    };
    var employerNew = {
        身份证: ctx.request.body.newID,
        部门号: ctx.request.body.newDepartNum,
        姓名: ctx.request.body.newName,
        家庭地址: ctx.request.body.newAddr,
        电话号码: ctx.request.body.newPhone,
        开始工作日期: ctx.request.body.newWorkTime
    };
    var option = ctx.request.body.option;
    deleteEmpty(employerExist);
    deleteEmpty(employerNew);
    deleteEmpty(peopleNew);
    if(option === 'Search'){
        var employers = await employer.findAll({
            where: employerExist
        });
    }
    else if(option === 'Create'){
         // if people table haven't got this employer, add it
        var peoples = await people.findAll({
            where: peopleNew
        });
        if(!peoples.length){
            await people.create(peopleNew);
        }
        var employers = await employer.create(employerNew);
        employers = [employerNew];
    }
    else if(option === 'Delete'){
        var employers = await employer.findAll({
            where: employerExist
        });
        for(let emp of employers){
            await emp.destroy();
        }
    }
    else if(option === 'Update'){
        var employers = await employer.findAll({
            where: employerExist
        });
        for(let emp of employers){
            Object.keys(employerNew).forEach(function(key){
                emp[key] = employerNew[key];
            });
            await emp.save();
        }
    }
    ctx.render(filepath, {employers: employers});
}

module.exports = {
    'POST /employer': post_employer
};
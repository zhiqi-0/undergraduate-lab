const Branch = require('../models/Branch');
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

function merge(obj1, obj2){
    var result = {};
    for(var key in obj1) result[key] = obj1[key];
    for(var key in obj2) result[key] = obj2[key];
    return result;
}

var post_branch = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/branch.html');
    var branchExist = {
        支行名: ctx.request.body.existName,
        所在城市: ctx.request.body.existLoc
    };
    var branchNew = {
        支行名: ctx.request.body.newName,
        所在城市: ctx.request.body.newLoc
    };
    var departmentExist = {
        部门名: ctx.request.body.existDepartName,
        部门号: ctx.request.body.existDepartNum,
        部门类型: ctx.request.body.existDepartType,
        部门经理身份证: ctx.request.body.existDepartMID,
        支行名: ctx.request.body.existName
    };
    var departmentNew = {
        部门名: ctx.request.body.newDepartName,
        部门号: ctx.request.body.newDepartNum,
        部门类型: ctx.request.body.newDepartType,
        部门经理身份证: ctx.request.body.newDepartMID,
        支行名: ctx.request.body.newName
    };
    deleteEmpty(branchExist);
    deleteEmpty(branchNew);
    deleteEmpty(departmentExist);
    deleteEmpty(departmentNew);
    var option = ctx.request.body.option || 'Search';
    if(option === 'Search'){
        console.log(JSON.stringify(branchExist));
        var branches = await Branch.branch.findAll({
            include: {model: Branch.department, where: departmentExist},
            where: branchExist
        });
    }
    else if(option === 'Create'){
        branches = await Branch.branch.findAll({
            where: branchNew
        });
        if(!Object.keys(branches).length){
            await Branch.branch.create(branchNew);
        }
        await Branch.department.create(departmentNew);
        branchNew['departments'] = [departmentNew];
        branches = [branchNew];
    }
    else if(option === 'Delete'){
        var branches = await Branch.branch.findAll({
            where: branchExist
        });
        for(let b of branches){
            // if statement
            var departs = await Branch.department.findAll({
                where:{
                    支行名: b.支行名
                }
            });
            for(let d of departs){
                await d.destroy;
            }
            await b.destroy();
        }
    }
    else if(option === 'Update'){
        var branches = await Branch.branch.findAll({
            where: branchExist
        });
        for(let b of branches){
            Object.keys(branchNew).forEach(function(key){
                b[key] = branchNew[key];
            });
            await b.save();
        }
    }
    console.log(JSON.stringify(branches));
    ctx.render(filepath, {branches: branches});
};

module.exports= {
    'POST /branch': post_branch
}
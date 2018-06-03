const branch = require('../models/branch');
const Sequelize = require('sequelize');
const fs = require('fs');
const path = require('path');

var post_branch = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/branch.html');
    console.log(ctx.request.body);
    var existName = ctx.request.body.existName || '';
    var existLoc = ctx.request.body.existLoc || '';
    var newName = ctx.request.body.newName || '';
    var newLoc = ctx.request.body.newLoc || '';
    var _exist = {支行名: existName, 所在城市: existLoc};
    var _new = {支行名: newName, 所在城市: newLoc};
    Object.keys(_exist).forEach(function(key) {
        if(_exist[key] === ''){
            delete _exist[key];
        }
    });
    Object.keys(_new).forEach(function(key) {
        if(_new[key] === ''){
            delete _new[key];
        }
    });
    var option = ctx.request.body.option || 'Search';
    if(option === 'Search'){
        var branches = await branch.findAll({
            where: _exist
        });
    }
    else if(option === 'Create'){
        var branches = await branch.create(_new);
        branches = [_new];
    }
    else if(option === 'Delete'){
        var branches = await branch.findAll({
            where: _exist
        });
        for(let b of branches){
            await b.destroy();
        }
    }
    else if(option === 'Update'){
        var branches = await branch.findAll({
            where: _exist
        });
        for(let b of branches){
            Object.keys(_new).forEach(function(key){
                b[key] = _new[key];
            });
            await b.save();
        }
    }
    ctx.render(filepath, {branches: branches});
};

module.exports= {
    'POST /branch': post_branch
}
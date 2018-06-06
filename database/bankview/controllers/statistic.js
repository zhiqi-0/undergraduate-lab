const db = require('../db');
const Sequelize = require('sequelize');
const fs = require('fs');
const path = require('path');


var get_statistic = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/statistic.html');
    var param = {};
    var employerNum = await db.query('select count(1) as num from `员工`');
    param.employerNum = employerNum[0][0].num;
    var customerNum = await db.query('select count(1) as num from `客户`');
    param.customerNum = customerNum[0][0].num;
    var branchNum = await db.query('select count(1) as num from `支行`');
    param.branchNum = branchNum[0][0].num;
    var creditNum = await db.query('select count(1) as num from `支票账户`');
    param.creditNum = creditNum[0][0].num;
    var savingNum = await db.query('select count(1) as num from `储蓄账户`');
    param.savingNum = savingNum[0][0].num;
    ctx.render(filepath, param);
};

module.exports = {
    'GET /statistic': get_statistic
};
const Sequelize = require('sequelize');
const db = require('../db');

var Employer = db.define('employer', {
    身份证: {
        type: Sequelize.STRING(30),
        primaryKey: true
    },
    部门号: Sequelize.NUMERIC({precision: 8, scale: 0}),
    姓名: Sequelize.STRING(20),
    家庭地址: Sequelize.STRING(30),
    电话号码: Sequelize.NUMERIC({precision: 8, scale: 0}),
    开始工作日期: Sequelize.DATE
},{
    timestamps: false,
    freezeTableName: true,
    tableName: '员工'
});

module.exports = Employer;
const Sequelize = require('sequelize');
const db = require('../db');

var People = db.define('customer', {
    身份证: {
        type: Sequelize.STRING(30),
        primaryKey: true
    },
    姓名: Sequelize.STRING(20),
    家庭地址: Sequelize.STRING(30),
    电话号码: Sequelize.NUMERIC({precision: 8, scale: 0})
},{
    timestamps: false,
    freezeTableName: true,
    tableName: '人员'
});

module.exports = People;
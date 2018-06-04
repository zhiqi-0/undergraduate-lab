const Sequelize = require('sequelize');
const db = require('../db');

var Customer = db.define('customer', {
    身份证: {
        type: Sequelize.STRING(30),
        primaryKey: true
    },
    员工_身份证: Sequelize.STRING(30),
    姓名: Sequelize.STRING(20),
    家庭地址: Sequelize.STRING(30),
    电话号码: Sequelize.NUMERIC({precision: 8, scale: 0}),
    联系人姓名: Sequelize.STRING(30),
    联系人手机: Sequelize.STRING(30),
    联系人邮箱: Sequelize.STRING(30),
    联系人关系: Sequelize.STRING(30)
},{
    timestamps: false,
    freezeTableName: true,
    tableName: '客户'
});

module.exports = Customer;
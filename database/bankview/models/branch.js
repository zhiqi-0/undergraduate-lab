const Sequelize = require('sequelize');
const db = require('../db');


var Branch = db.define('branch', {
    支行名: {
        type: Sequelize.NUMERIC({precision: 8, scale: 0}),
        primaryKey: true
    },
    所在城市: Sequelize.STRING(20)
}, {
    timestamps: false,
    freezeTableName: true,
    tableName: '支行'
});

var Department = db.define('department', {
    部门号: {
        type: Sequelize.NUMERIC({precision: 8, scale: 0}),
        primaryKey: true
    },
    部门名: Sequelize.STRING(30),
    部门类型: Sequelize.STRING(30),
    部门经理身份证: Sequelize.STRING(30),
    支行名: Sequelize.NUMERIC({precision: 8, scale: 0})
}, {
    timestamps: false,
    freezeTableName: true,
    tableName: '部门'
});

Branch.hasMany(Department, {foreignKey: '支行名'});

module.exports = {
    branch: Branch,
    department: Department
};
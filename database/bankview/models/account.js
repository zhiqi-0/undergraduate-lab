const Sequelize = require('sequelize');
const db = require('../db');


var Account = db.define('account', {
    账户号: {
        type: Sequelize.NUMERIC({precision: 20, scale: 0}),
        primaryKey: true
    },
    余额: Sequelize.INTEGER,
    开户日期: Sequelize.DATE,
    最近访问日期: Sequelize.DATE
}, {
    timestamps: false,
    freezeTableName: true,
    tableName: '账户'
});

var SavingAccount = db.define('saveingAccount', {
    账户号: {
        type: Sequelize.NUMERIC({precision: 20, scale: 0}),
        primaryKey: true
    },
    余额: Sequelize.INTEGER,
    开户日期: Sequelize.DATE,
    最近访问日期: Sequelize.DATE,
    利率: Sequelize.DOUBLE,
    货币类型: Sequelize.STRING(20)
}, {
    timestamps: false,
    freezeTableName: true,
    tableName: '储蓄账户'
});

var CreditAccount = db.define('creditAccount', {
    账户号: {
        type: Sequelize.NUMERIC({precision: 20, scale: 0}),
        primaryKey: true
    },
    余额: Sequelize.INTEGER,
    开户日期: Sequelize.DATE,
    最近访问日期: Sequelize.DATE,
    透支额: Sequelize.DOUBLE
}, {
    timestamps: false,
    freezeTableName: true,
    tableName: '支票账户'
});

module.exports = {
    'account': Account,
    'savingAccount': SavingAccount,
    'creditAccount': CreditAccount
};
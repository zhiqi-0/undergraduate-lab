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

var OpenAccount = db.define('openAccount', {
    身份证: {
        type: Sequelize.STRING(30),
        primaryKey: true
    },
    账户号: {
        type: Sequelize.NUMERIC({precision: 20, scale: 0}),
        primaryKey: true
    },
    开户行: Sequelize.STRING(30),
    账户类型: Sequelize.STRING(30)
}, {
    timestamps: false,
    freezeTableName: true,
    tableName: '开户'
});

module.exports = {
    'account': Account,
    'savingAccount': SavingAccount,
    'creditAccount': CreditAccount,
    'openAccount': OpenAccount
};
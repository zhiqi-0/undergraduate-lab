const Sequelize = require('sequelize');
const db = require('../db');

var Loan = db.define('loan', {
    贷款号: {
        type: Sequelize.NUMERIC({precision:8, scale: 0}),
        primaryKey: true
    },
    支行名: Sequelize.STRING(20),
    贷款金额: Sequelize.DOUBLE,
    总共支付次数: Sequelize.BIGINT
}, {
    timestamps: false,
    freezeTableName: true,
    tableName: '贷款'
});

var Payment = db.define('Payment', {
    支付序号: {
        type: Sequelize.DECIMAL,
        primaryKey: true
    },
    贷款号: {
        type: Sequelize.NUMERIC({precision: 8, scale: 0}),
        primaryKey: true
    },
    身份证: Sequelize.STRING(30),
    支付金额: Sequelize.DOUBLE
}, {
    timestamps: false,
    freezeTableName: true,
    tableName: '支付'
});

module.exports = {
    'loan': Loan,
    'payment': Payment
};
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

module.exports = Loan;
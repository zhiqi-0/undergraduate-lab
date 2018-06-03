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

module.exports = Branch;
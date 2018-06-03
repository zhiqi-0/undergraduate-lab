const Sequelize = require('sequelize');
const config = require('./config');


console.log('init sequelize...');

// connect mysql
var sequelize = new Sequelize(config.database, config.username, config.password, {
    host: config.host,
    pool: {
        max: 5,
        min: 0
    }
});

module.exports = sequelize;
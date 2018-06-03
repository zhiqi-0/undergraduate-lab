var fs = require('fs');
var path = require('path');

var get_login = async (ctx, next) => {
    //var rs = fs.createReadStream(__dirname + '/../view/login.html', 'utf8');
    var filepath = path.resolve(__dirname + '/../views/login.html');
    ctx.response.type = 'html';
    ctx.response.body = fs.createReadStream(filepath, 'utf8');
};

var post_login = async (ctx, next) => {
    var account = ctx.request.body.account || '';
    var password = ctx.request.body.password || '';
    console.log(`sign in with account: ${account}, password: ${password}`);
    if(account === 'zhiqilin' && password === '123456'){
        var filepath = path.resolve(__dirname + '/../views/manager.html');
        ctx.response.type = 'html';
        ctx.response.body = fs.createReadStream(filepath, 'utf8');
    }
    else{
        ctx.response.body = `<h1>Try again</h1>`;
    }
};

module.exports = {
    'GET /': get_login,
    'POST /login': post_login
};
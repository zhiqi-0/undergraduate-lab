const fs = require('fs');
const path = require('path');

var post_manager = async (ctx, next) => {
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
}

var get_manager = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/manager.html');
    ctx.response.type = 'html';
    ctx.render(filepath, {});
}

var get_branch = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/branch.html');
    ctx.response.type = 'html';
    ctx.render(filepath, {});
}

var get_employer = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/employer.html');
    ctx.response.type = 'html';
    ctx.render(filepath, {});
}

var get_customer = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/customer.html');
    ctx.response.type = 'html';
    ctx.render(filepath, {});
}

var get_account = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/account.html');
    ctx.response.type = 'html';
    ctx.render(filepath, {});
}

var get_loan = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/loan.html');
    ctx.response.type = 'html';
    cctx.render(filepath, {});
}

var get_statistic = async (ctx, next) => {
    var filepath = path.resolve(__dirname + '/../views/statistic.html');
    ctx.response.type = 'html';
    ctx.render(filepath, {});
}

module.exports = {
    'POST /manager': post_manager,
    'GET /manager': get_manager,
    'GET /branch': get_branch,
    'GET /employer': get_employer,
    'GET /customer': get_customer,
    'GET /account': get_account,
    'GET /loan': get_loan,
    'GET /statistic': get_statistic
};
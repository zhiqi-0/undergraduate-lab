const Koa = require('koa');

const bodyParser = require('koa-bodyparser');

const controller = require('./controller');

const isProduction = process.env.NODE_ENV === 'production';

const templating = require('./templating')

const app = new Koa();

// log information
app.use(async (ctx, next) => {
    console.log(`Receive ${ctx.request.method}: ${ctx.request.url}`);
    await next();
});

// static file support:
if (! isProduction) {
    let staticFiles = require('./static-files');
    app.use(staticFiles('/static/', __dirname + '/static'));
}

// add request parser middleware
app.use(bodyParser());

// add nunjucks as view
app.use(templating('views', {
    noCache: !isProduction,
    watch: !isProduction
}));

// add url mapping and handling controller
app.use(controller());

// start listening
app.listen(3000);
console.log('app started at port 3000...');
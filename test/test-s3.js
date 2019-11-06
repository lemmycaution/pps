const Parser = require('../ern/parser/lib');
const { PassThrough } = require('stream');
const { createReadStream } = require('../io')

const files = require('./fixtures/files.json')

function parseTest(url) {
  return new Promise((resolve, reject) => {
    const rs = createReadStream(url.replace("s3://primephonic-ddex-storage-acc/originals", `file://${__dirname}/fixtures`));
    const ws = new PassThrough; //process.stdout;
    const parser = new Parser();

    parser.on('pipe', () => {
      console.time('parser:' + url);
      // console.log('PIPE Event:' + url);
    });
    parser.on('unpipe', () => {
      // console.log('UNPIPE Event:' + url);
    });
    parser.on('finish', () => {
      console.timeEnd('parser:' + url);
      // console.log('FINISH Event:' + url);
    });
    parser.on('error', (e) => {
      // console.log('ERROR Event: ' + url, e);
      reject(e)
    });
    parser.on('end', () => {
      // console.log('END Event' + url);
      resolve(url)
    });

    rs.pipe(parser).pipe(ws);
  });
}

console.time('parser:all')
// parseTest(files[54])
Promise.all([files[52],files[53],files[54]].map(file => parseTest(file))).then(() => console.timeEnd('parser:all'))
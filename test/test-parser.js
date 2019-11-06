const Parser = require('../ern/parser/lib');
const fs = require('fs');
const assert = require('assert');


const parser = new Parser();

const rs = fs.createReadStream(__dirname + '/fixtures/lg.xml');
const ws = fs.createWriteStream(__dirname + '/fixtures/lg.json');

parser.on('pipe', () => {
  console.time('parser');
  console.log('PIPE Event');
});
parser.on('unpipe', () => {
  console.log('UNPIPE Event');
});
parser.on('finish', () => {
  console.log('FINISH Event');
});
parser.on('error', (e) => {
  console.log('ERROR Event', e);
});
parser.on('end', () => {
  console.timeEnd('parser');
  console.log('END Event');
  const rsc = fs.readFileSync(__dirname + '/fixtures/lg.xml').toString();
  const wsc = fs.readFileSync(__dirname + '/fixtures/lg.json').toString();
  const tags = ['MessageHeader', 'SoundRecording', 'Release', 'ReleaseDeal'];
  tags.forEach(tag => {
    const c1 = count(rsc, `</${tag}>`);
    const c2 = count(wsc, `"${tag}":{`);
    assert.equal(c1, c2, tag);
  })
});

rs.pipe(parser).pipe(ws);

function count(temp, k) {
  return (temp.match(new RegExp(k, 'g')) || []).length;
}
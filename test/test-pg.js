const Parser = require('../ern/parser/lib');
const fs = require('fs');
const assert = require('assert');
const { createReadStream, createWriteStream } = require('../io')

const ps = new Parser({csv: true})
const rs = createReadStream(`file://${__dirname}/fixtures/lg.xml`)
const pg = createWriteStream(`postgresql://localhost/ddex/tmp`)

console.time('postgres')
rs.pipe(ps).pipe(pg)
  .on('finish', () => console.timeEnd('postgres'))

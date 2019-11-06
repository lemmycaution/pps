const Parser = require('../ern/parser/lib');
const fs = require('fs');
const assert = require('assert');
const { createReadStream, createWriteStream } = require('../io')

const ps = new Parser({objectMode: true})
const rs = createReadStream(`file://${__dirname}/fixtures/xs.xml`) //set-2019-2-F-20190916.zip
const md = createWriteStream(`mongodb://localhost:27017/ddex/tmp`)

console.time('mongodb')
rs.pipe(ps).pipe(md)
  .on('finish', () => console.timeEnd('mongodb'))


'use strict'

const { createReadStream, createWriteStream } = require('../io')
const { PassThrough } = require('stream')


function test_postgresql_write() {
  const url = 'postgresql://localhost/ddex/tmp'
  const stream = createWriteStream(url)
  stream.on('error', console.error)
  stream.write('{"hello": "world"}')
  stream.end()
}

test_postgresql_write()

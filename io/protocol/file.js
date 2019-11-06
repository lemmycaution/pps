'use strict'

const { join } = require('path')
const { createReadStream } = require('fs')

module.exports.createReadStream = ({ host, path }) => createReadStream(join(host, path))

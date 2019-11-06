'use strict'

const { parse } = require('url')
const { join, basename } = require('path')
const { existsSync } = require('fs')
const unzipper = require('unzipper')
const { Transform } = require('stream')

function parseUrl(url) {
  const { protocol, hostname, pathname, ...rest } = parse(url)
  return {
    protocol: protocol.substr(0, protocol.length - 1),
    host: hostname,
    path: pathname,
    ...rest
  }
}

function parseZip(rs) {
  return rs
    .pipe(unzipper.Parse())
    .pipe(new Transform({
      objectMode: true,
      transform(entry, e, cb) {
        if(!entry.path.endsWith('.xml')) {
          entry.autodrain().then(() => cb())
        } else {
          entry.on('data', data => this.push(data)).on('end', cb)
        }
      }
    }))
}

function requireProtocol(protocol) {
  const _module = join(__dirname, 'protocol', `${protocol}.js`)
  if (!existsSync(_module)) {
    throw new Error(`NotImplemented [protocol: ${protocol}]`)
  }
  return require(_module)
}

function requireProtocolMethod(protocol, method) {
  const _module = requireProtocol(protocol)
  const implementation = _module[method]
  if (typeof implementation !== 'function') {
    throw new Error(`NotImplemented [method ${protocol}.${method}]`)
  }
  return implementation
}

module.exports.createReadStream = (url) => {
  const resource = parseUrl(url)
  const rs = requireProtocolMethod(resource.protocol, 'createReadStream')(resource)
  if (url.endsWith('.zip')) {
    return parseZip(rs)
  }
  return rs
}

module.exports.createWriteStream = (url) => {
  const resource = parseUrl(url)
  return requireProtocolMethod(resource.protocol, 'createWriteStream')(resource)
}

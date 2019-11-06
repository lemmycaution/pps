const { Transform } = require('stream')
const { Parser } = require('bindings')('ern-parser')
const {inherits} = require('util')
const crypto = require('crypto')


inherits(Parser, Transform)

class ParserStream extends Transform {
  constructor({csv, ...opts} = {}) {
    super(opts)
    this._mode = csv ? 2 : opts.objectMode ? 1 : 0
    this._parser = new Parser(opts)
  }

  write(chunk) {
    this._parser.transform(chunk, (err, json) => {
      if (err) {
        this.emit('error', err)
        return
      }
      // COPY WAY | is fake quote char to trick psql COPY method, \n is row delimeter
       if (this._mode === 0)
         this.push(json)
       else if (this._mode === 1)
         this.push({
           ...JSON.parse(json),
           Hash: crypto.createHash('md5').update(json).digest('hex')
         })
       else
         this.push(`|${json}|\n`)
       if (this._ended) {
         this._finish()
       }
    })
  }
  end(chunk) {
    this._ended = true
    if (chunk) {
      this.write(chunk)
    } else {
      this._finish()
    }
  }
  _finish() {
    if (this._int) {
       clearTimeout(this._int)
     }
     this._int = setTimeout(() => {
       this.push(null)
       this.emit('finish')
     }, 10)
  }
}

module.exports = ParserStream


'use strict'

const { join } = require('path')
const { Writable } = require('stream')
const Libpq = require('libpq')
const POOL = {}
class PostgresqlWritable extends Writable {
  static get pool() {
    return POOL
  }
  constructor({auth, host, path, ...opts}) {
    super(opts)

    const [_, db, table ] = path.split('/')
    const url = `postgresql://${auth || ''}${host}/${db}`

    this.table = table
    this.pg = PostgresqlWritable.pool[url]
              || (PostgresqlWritable.pool[url] = new Libpq())

    if (!this.pg.connected)
      this.pg.connectSync(url)

    this.pg.setNonBlocking(true)

    this.on('error', (e) => {
      console.error(e)
      this.pg.clear()
    })

    // COPY WAY
    this.pg.exec(`COPY ${table}(data) FROM stdin WITH CSV QUOTE '|'`)
    if (this.pg.resultStatus() !== 'PGRES_COPY_IN') {
      this.emit('error', this.pg.resultErrorMessage())
    }
  }

  _write(chunk, enc, cb) {
    // INSERT WAY
    // let err
    // let value = this.pg.escapeLiteral(chunk.toString())
    // let sent = this.pg.sendQuery(`INSERT INTO ${this.table}(data) VALUES(${value});`);
    // if(!sent) return cb(new Error(this.pg.errorMessage()))
    // while(this.pg.getResult()) {
    //   if (err = this.pg.errorMessage())
    //     break
    // }
    // cb(err)

    // COPY WAY
    const res = this.pg.putCopyData(chunk)
    if (res < 0)
      cb(this.pg.resultErrorMessage())
    else
      cb()
  }

  _final(cb) {
    let err
    // COPY WAY
    this.pg.putCopyEnd()
    while(this.pg.getResult()) {
      if (err = this.pg.errorMessage())
        break
    }
    this.pg.clear()
    cb(err)
  }
}

module.exports.createWriteStream =
  ({ host, path, auth }) => new PostgresqlWritable({ host, path, auth })

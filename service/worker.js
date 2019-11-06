const Parser = require('../ern/parser/lib')
const { createReadStream, createWriteStream } = require('../io')
const mubsub = require('mubsub')
const mongo = require('../db/mongo')

async function start(){

  const db = await mongo.db('ddex')
  const collection = await db.collection('ern')
  const pubsub = mubsub(mongo.url)
  const channel = pubsub.channel('ern_c')
  pubsub.on('error', console.error)
  channel.on('error', console.error)
  channel.subscribe('queue', async function (url) {
    await collection.updateOne({url}, {$set: {url,status: 'processing'}}, {upsert: true})

    const dst = `${mongo.url}/tmp`

    const r = createReadStream(url)
    const p = new Parser({objectMode: true})
    const w = createWriteStream(dst)
    const e = (e) => collection.updateOne({url}, {$set: {status: 'error', error: e.message}})

    r.on('error', e)
    p.on('error', e)
    w.on('error', e)

    w.on('close', () => {
      collection.updateOne({url}, {$set: { status: 'done' }})
    })

    r.pipe(p).pipe(w).on('error', e)
  })
}

start()

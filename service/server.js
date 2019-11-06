'use strict'

const express = require('express')
const mubsub = require('mubsub')
const mongo = require('../db/mongo')

async function start(){

  const db = await mongo.db('ddex')
  const collection = await db.collection('ern')
  const pubsub = mubsub(mongo.url)
  const channel = pubsub.channel('ern_c')
  pubsub.on('error', console.error)
  channel.on('error', console.error)

  const app = express()

  app.use(express.json())

  app.post('*', async function(req, res) {
    try {
      const { url, force } = req.body

      const file = await collection.findOne({url})

      if (file) {
        if (file.status !== 'done' && force) {
          channel.publish('queue', url)
          res.json({status: 'queue'})
        } else {
          res.status(406).json(file)
        }
      } else {
        channel.publish('queue', url)
        res.json({status: 'queue'})
      }
    } catch (e) {
      res.status(500).json({error: e.message})
    }
  })

  app.listen(3000)

}

start()
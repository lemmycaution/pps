'use strict'

const { streamToMongoDB } = require('../../lib/stream-to-mongo-db')

module.exports.createWriteStream =
  ({ href }) => {
    href = href.split('/')
    const collection = href.pop()
    const dbURL = href.join('/')
    return streamToMongoDB({ dbURL, collection, batchSize: 500, upsert: true })
  }

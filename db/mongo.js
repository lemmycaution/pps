'use strict'

const { MongoClient } = require('mongodb');

const DATABASE_URL = 'mongodb://localhost:27017/ddex'
const opts = { useNewUrlParser: true, useUnifiedTopology: true }


module.exports.url = DATABASE_URL
module.exports.db = async (name) => {
  const client = await MongoClient.connect(DATABASE_URL, opts);
  return client.db(name)
}
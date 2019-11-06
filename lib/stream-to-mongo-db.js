// forked from https://github.com/AbdullahAli/node-stream-to-mongo-db/blob/master/src/index.js

'use strict'

const { Writable } = require('stream');
const { MongoClient } = require('mongodb');

module.exports = {
  streamToMongoDB: (options) => {
    const config = Object.assign(
      // default config
      {
        batchSize: 1,
        insertOptions: { w: 1 },
      },
      // overrided options
      options,
    );

    // those variables can't be initialized without Promises, so we wait first drain
    let client;
    let dbConnection;
    let collection;
    let records = [];
    let writable;

    // this function is usefull to insert records and reset the records array
    const insert = async (s) => {
      if (config.upsert) {
        // await collection.bulkWrite(records.map(r => ({
        //   updateOne: {
        //     filter: { Hash: r.Hash },
        //     update: { $set: r },
        //     upsert: true
        //   }
        // })))
        await Promise.all(records.map(r => collection.updateOne(
          { Hash: r.Hash },
          { $set: r },
          { upsert: true }
        ).then(({result}) => {
          console.log()
          writable.emit('result', {result, hash: r.Hash})
        })))
      } else {
        await collection.insertMany(records, config.insertOptions);
      }

      records = [];
    };

    const close = async () => {
      if (!config.dbConnection && client) {
        await client.close();
      }
    };

    // stream
    writable = new Writable({
      objectMode: true,
      write: async (record, encoding, next) => {
        try {
          // connection
          if (!dbConnection) {
            if (config.dbConnection) {
              dbConnection = config.dbConnection; // eslint-disable-line prefer-destructuring
            } else {
              client = await MongoClient.connect(config.dbURL, { useNewUrlParser: true, useUnifiedTopology: true });
              dbConnection = await client.db();
            }
          }
          if (!collection) collection = await dbConnection.collection(config.collection);

          // add to batch records
          records.push(record);

          // insert and reset batch recors
          if (records.length >= config.batchSize) await insert();

          // next stream
          next();
        } catch (error) {
          await close();
          writable.emit('error', error);
        }
      }
    });

    writable.on('finish', async () => {
      try {
        if (records.length > 0) await insert();
        await close();

        writable.emit('close');
      } catch(error) {
        await close();

        writable.emit('error', error);
      }
    });

    return writable;
  },
};

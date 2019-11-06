'use strict'

const { join } = require('path')
const S3 = require('aws-sdk/clients/s3')
const { AWS_ACCESS_KEY_ID, AWS_SECRET_ACCESS_KEY } = process.env
const DEFAULT_AUTH = `${AWS_ACCESS_KEY_ID}:${AWS_SECRET_ACCESS_KEY}`

function creds(auth) {
  let [ accessKeyId, secretAccessKey ] = auth.split(':')
  return { accessKeyId, secretAccessKey }
}

function s3(auth) {
  let clients = s3.clients || {}
  return clients[auth] || (clients[auth] = new S3(creds(auth)))
}

module.exports.createReadStream =
  ({ host: Bucket, path: Key, auth }) =>
    s3(auth || DEFAULT_AUTH).getObject({ Bucket, Key }).createReadStream()
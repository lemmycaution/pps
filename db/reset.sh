#!/bin/sh

dir=$(dirname $0)

psql -c "DROP DATABASE ddex"
psql -c "CREATE DATABASE ddex"
psql ddex -f $dir/setup.sql

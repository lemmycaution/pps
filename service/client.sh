URL=$1
curl -X POST \
-H 'Content-Type: application/json' \
-d "{\"url\":\"$URL\"}" http://localhost:3000

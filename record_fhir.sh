#!/bin/bash

sox -d -b 16 -c 1 -r 16k $1

echo "done recording $1"
echo "saving $1..."

data=$(curl -XPOST 'https://api.wit.ai/speech?v=20160526' \
   -L \
   -H "Authorization: Bearer JMR7MT2KOXLPCYCKATTVIAJ4PWZEVKGU" \
   -H "Content-Type: audio/wav" \
   --data-binary "@$1" )

node fhir.js $data

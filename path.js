const response = process.argv

response.splice(0, 2)

const Json = JSON.parse(response.join(' '))
let direction = ''

if(Json.entities.direction){
  direction = Json.entities.direction[0].value
} else {
  direction = 'empty'
}
console.log(direction)
console.log('text:', Json._text)

const http = require('http')
const querystring = require('querystring')

const postData = querystring.stringify({
  'direction' : direction
});

const options = {
  hostname: '192.168.43.182',
  port: 8080,
  path: '/path',
  method: 'POST',
  headers: {
    'Content-Type': 'application/x-www-form-urlencoded',
  }
};

const req = http.request(options, (res) => {
  console.log(`STATUS: ${res.statusCode}`);
  console.log(`HEADERS: ${JSON.stringify(res.headers)}`);
  res.setEncoding('utf8');
  res.on('data', (chunk) => {
    console.log(`BODY: ${chunk}`);
  });
  res.on('end', () => {
    console.log('No more data in response.');
  });
});

req.on('error', (e) => {
  console.log(`problem with request: ${e.message}`);
});

// write data to request body
req.write(postData);
req.end();

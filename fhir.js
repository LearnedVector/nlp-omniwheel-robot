var express = require('express');
var app = express();

const response = process.argv.splice(2,process.argv.length)
const Json = JSON.parse(response.join(' '))
let name = ''
let urlParams = ''
let findAllergies = false
let allergies = new Set();

let options = {
  host: `fhir-open-api-dstu2.smarthealthit.org`,
  path: '',
  headers: {
    'Accept': 'application/json',
  },
};

if(Json.entities.contact && Json.entities.fhir){
  console.log(Json.entities.contact[0].value, Json.entities.fhir[0].value)
  findAllergies = true
  name = Json.entities.contact[0].value
  urlParams = `/${Json.entities.fhir[0].value}?name=${name}`
  options.path = urlParams
}

if(!Json.entities.fhir){
  name=Json.entities.contact[0].value
  urlParams = `/Patient?name=${name}`
  options.path = urlParams
}

// console.log(Json)
// const name = Json.entities.contact[0].value

console.log('name extracted is: ', name)

let patientInfo = ''
let bufferArray = []
const https = require('https')

https.get(options, (res) => {
  console.log('statusCode:', res.statusCode);
  console.log('headers:', res.headers);

  res.on('data', (d) => {
    bufferArray.push(d)
  }).on('end', () => {
    patientInfo = JSON.parse(Buffer.concat(bufferArray).toString())
    if(findAllergies == true){
      patientInfo.entry.map(entry => {
        allergies.add(entry.resource.substance.text)
      })
      console.log(allergies)
    }
  });

}).on('error', (e) => {
  console.error(e);
});

app.set('view engine', 'pug');
app.get('/', function (req, res) {
  if(findAllergies == false){
    res.render('index', { patient: patientInfo });
  }else{
    res.render('allergies', { patient: patientInfo, name: name, allergies: [...allergies]})
    // res.send(allergies)
  }
})

var server = app.listen(3000, function () {

  var host = server.address().address
  var port = server.address().port
  console.log("Example app listening at http://%s:%s", host, port)
})

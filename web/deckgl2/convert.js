const csvToJson = require('convert-csv-to-json');
 
const input = './lora3.csv'; 
const output = './public/lora.json';
 
csvToJson.fieldDelimiter(',')
         .formatValueByType()
         .generateJsonFileFromCsv(input, output);
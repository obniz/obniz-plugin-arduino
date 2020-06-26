const fs = require('fs');


console.log("Node Build start");

if((process.argv.length - 2) !== 5){
    console.error("引数が不足しています");
}

const URL = process.argv[2];
const CHECK_SUM = process.argv[3];
const SIZE = process.argv[4];
const FILE_NAME = process.argv[5];
const VERSION = process.argv[6];


let jsonObject = JSON.parse(fs.readFileSync('./docs/package_obniz_index.json', 'utf8'));

jsonObject.packages[0].platforms.push(
    {
        "category": "ESP32",
        "name": "obniz",
        "architecture": "esp32",

        "url": URL,
        "checksum": CHECK_SUM,
        "size": SIZE,
        "archiveFileName": FILE_NAME,
        "version": VERSION,

        "help": {
            "online": ""
        },
        "boards": [
            {
                "name": "obniz"
            }
        ],
        "toolsDependencies": [
            {
                "packager": "obniz",
                "version": "1.22.0-80-g6c4433a-5.2.0",
                "name": "xtensa-esp32-elf-gcc"
            },
            {
                "packager": "obniz",
                "version": "2.6.1",
                "name": "esptool_py"
            },
            {
                "packager": "obniz",
                "version": "0.2.3",
                "name": "mkspiffs"
            }
        ]
    }
);

fs.writeFileSync('./docs/package_obniz_index.json', JSON.stringify(jsonObject,null , "  "));

console.log("Node Build end");
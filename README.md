# Arduino core for the obniz

Arduinoとしてobnizの機能を扱えるようになるプラグインになります。

## リリースメモ

スクリプトを用意しておいたので、バージョンを指定するとArduinoで配布するために必要なファイルとJsonのデータを自動的に生成してくれます。

```shell script
$ bash build.sh
versionを入力してください
0.0.1

files copy
- cores copied
- libraries copied
- tools copied
- variants copied
- settingfiles copied
Create zip file
Created zip file
Get checksum & file size

Package.json info

"url": "http://obniz.io/obniz-v0.0.1.zip",
"checksum": "SHA-256:3390a65d9a32de88beb67af73f05821e8de4625283f2734749d9c55ebc66abc4",
"size": "50601568",
"archiveFileName": "obniz-v0.0.1.zip",
"version": "0.0.1",
```

別管理されているPackage.jsonを上記の情報を参考に追記すると配布が容易になります。
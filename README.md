# LoRaWAN_data_visualize
sensor data visualizing by loRaWAN, Node-RED and Ambient

センスウェイ社のLoRaWANスターターキットを利用したシステム構築

## LoRaWAN設定
1. アカウント作成、デバイスの登録、ゲートウェイの利用と申込み
  SenseWay Mission Connectにアカウントを作成し、モジュールを登録、アカウントに紐づけます。

   https://console.senseway.net/login

2. ゲートウェイをインターネットと接続する  
  LoRaWANレンタルゲートウェイ（G-BOX）使用方法を参照  
  https://www.senseway.net/service/network-service/network-manual/lorawangateway_gbox_manual/  
  ゲートウェイの4つのLED点灯　でOK

3. ArduinoとLoRaWAN通信モジュールを接続する

4. Kashiwa Geeksライブラリを導入する  
  https://github.com/ty4tw/KashiwaGeeks  
  Arduino IDEを起動し、「スケッチ」→「ライブラリをインクルード」→「.zip形式のライブラリをインストール」で、先ほどダウンロードしたzipファイルを選択し、インストールします。  
  「スケッチ」→「ライブラリをインクルード」の中の下の方に「KashiwaGeeks-master」があれば、インストールは成功です。  
  ツール→シリアルモニタ→57600bps  
  ファイル→スケッチ例→KashiwaGeeksMaster→End-node_Sample
をarduinoにロード  
  システムモニタに「SUCCESS」と表示されれば成功

## Node-RED設定(local)
1. Node.jsインストール  
  https://nodejs.org/ja/download/   
  からダウンロードしたインストーラ実行  
  コマンドプロンプトから下記のコマンドを実行して確認
```
    node --version  
```

2. Node-REDインストール
```
    npm install -g --unsafe-perm node-red 
```

4. nodeの追加
```
    npm i node-red-contrib-kgpcomposer
    npm i node-red-contrib-kgpparser
    npm i node-red-contrib-senseway
    npm i node-red-contrib-ambient
```

5. Node-RED起動
```
    node-red 
```

6. ブラウザからhttp://localhost:1880 へアクセス  
  Node-REDの左側ペインに inject, kgpcomposer, kgpparser, senseway, ambient
 ノードが 表示されている

## Node-RED設定(IBM-Cloud)

工事中


## ambient設定(IoTデーターの可視化サービス)
1. アカウント作成  
  https://ambidata.io/

2. ログインする  
  https://ambidata.io/ch/channels.html

3. チャンネルを作る
「チャンネルを作る」ボタンを押す

4. チャートを作る  
  Myチャンネルボタンを押す  
  チャート追加ボタンを押す


## 参考情報
* LoRaWANスターターキットの資料
  * https://www.senseway.net/document-starter-kit/
* ゲートウェイの接続
  * https://www.senseway.net/service/network-service/network-manual/lorawangateway_gbox_manual/
* センスウェイ社のLoRaWANスターターキットで温度計IoTしてみた！
  * https://chasuke.com/sensewaylorawan/
* ArduinoとLoRaWANモジュールでデータを送信する
  * https://qiita.com/takamachi1saki/items/03952069972b2d10fa64
* センスウェイさんのLoRaWANスターターキットを試してみた - サーバーレスにセンサデータ取得&可視化
 * http://tokina.hatenadiary.jp/entry/20190131_Senseyway_Kit_Serverless

## License

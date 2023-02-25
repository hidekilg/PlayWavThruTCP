#include <WiFi.h>
#include <M5Stack.h>

#include "AudioFileSourceSD.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

const char* ssid = "<SSID>"; // SSID
const char* password = "PASSWORD"; // PASSWORD

WiFiServer server(10000);	// TCP待ち受けポート番号

AudioGeneratorWAV *wav;
AudioFileSourceSD *wavfile;
AudioOutputI2S *out;

void setup()
{
    M5.begin();
    delay(100);
    M5.Lcd.setTextSize(2);  // 文字サイズ
    M5.Lcd.println("Connecting");

    // wifi接続開始
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        M5.Lcd.print(".");
    }

    // 接続完了したらIP表示
    M5.Lcd.println("Successed");
    M5.Lcd.println("IP: ");
    M5.Lcd.println(WiFi.localIP());
  
    server.begin();
}

void loop(){
  WiFiClient client = server.accept();  // クライアントからの接続を待ち受ける

  if (client) {
    M5.Lcd.println("New Client.");
    int bytes_received = 0;            // 受信したデータのサイズ     
    uint8_t header[] = {0,0,0,0};      // 受信するwavファイルのサイズを4バイトで受け取るための配列
    int message_length = 0;            // 受信するwavファイルのサイズ

    // wavファイルのサイズを知るため、まず4byteのデータを受信する
    while(bytes_received < 4) {
      if (client.available()) {
        header[bytes_received] = client.read();
 //       M5.Lcd.print(header[bytes_received]);
 //       M5.Lcd.print(' ');
        bytes_received++;
        delay(1);
      }
    }

    // 受信した4byteのデータからwavファイルのサイズを計算する
    for(int i=0 ;i<4;i++){
      message_length=message_length+header[i]*pow(256,3-i);
    }
//  M5.Lcd.println(message_length);

    uint8_t data ;
    bytes_received=0;
    
    // 受信するwavファイルの保存先となるSDカード上のファイルを書込モードで開く
    File file = SD.open("/output.wav",FILE_WRITE );

    // wavファイルのデータを受信し、SDカードに保存する
    while(bytes_received<message_length) {
      int size=client.available();
      if(size){
        for (int i = 0; i < size; i++) {
          data =client.read();
          file.write(data);
//          if(bytes_received<5){
//          M5.Lcd.print(data);
//          M5.Lcd.print(" ");
//          }
          bytes_received++; 
        }
      }
    }
    file.close();
    
    M5.Lcd.println(message_length);
    delay(100);
    client.stop();      // 接続を閉じる
//   M5.Lcd.println("client.stop()");

    // 受信したwavファイルを再生する
    wavfile = new AudioFileSourceSD("/output.wav");
    out = new AudioOutputI2S(0, 1); // Output to builtInDAC
    out->SetOutputModeMono(true);
    wav = new AudioGeneratorWAV();
    wav->begin(wavfile, out);

    while(true){
      if (wav->isRunning()) {
        if (!wav->loop()){
          wav->stop();
        }
      } else {
        Serial.printf("WAV done\n");
        delay(1000);
        break;
      }
    }
  }
}
# PlayWavThruTCP
  
【ファイル説明】 
  
・PlayWavThruTCP.ino  

Arduino IDE(初版は2.0.4-nightly-20230219)で作成されたプログラムソース  
TCPソケットサーバとして動作し、クライアントから送られてきたwavデータを再生する  
通信伝文のフォーマットは、受信するwavデータのバイト長(4byte)に続いて、wavデータ(任意長)としている  
wavデータの保存先としてSDカードを使用する  
WifiのSSIDとパスワード、およびTCPの待ち受けポート番号は適宜変更してご使用ください  
  
・SAPItoTCP.ps1  
  
「PlayWavThruTCP.ino」の動作確認を行うためのPowerShellスクリプト  
WindowsOS上で入力した文字列を音声合成し、そのデータをTCPソケットでデバイス(M5stackなど)に送信する  
接続先となるデバイスのIPアドレスとポート番号を適宜変更してご使用ください  
  
実行方法は以下の通り  
1) SAPItoTCP.ps1をWindows上の任意の場所に置く  
2) PowerShellを管理者権限で起動  
3) C:\> powershell -ExecutionPolicy RemoteSigned
4) C:\> Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
5) C:\> C:\[任意の場所]\SAPItoTCP.ps1  
  
【ライセンス】  
  
複製、改変、配布自由

# PlayWavThruTCP

【ファイル説明】
・PlayWavThruTCP.ino
　Arduino IDEのプログラムソース(2.0.4-nightly-20230219)
　WifiのSSIDとパスワード、およびTCPの待ち受けポート番号は適宜変更してご使用ください。

・SAPItoTCP.ps1
　M5stackに接続して動作確認を行うためのPowerShellスクリプト
　接続先となるM5stackのIPアドレスとポート番号を適宜変更してご使用ください。

【Windows側の実行方法】
1) socket_client.ps1を任意の場所に置く
2) Windowsキー ＋ R 押下してPowerShellを起動
3) C:\> powershell -ExecutionPolicy RemoteSigned
4) C:\> C:\[任意の場所]\socket_client.ps1

【ライセンス】
複製、改変、配布自由

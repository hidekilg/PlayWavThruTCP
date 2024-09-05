Clear-Host
Write-Host "Key in a sentence after >>: or press [q] to quit" -ForegroundColor Red -BackgroundColor White

#$ipaddress="127.0.0.1"
$ipaddress="192.168.100.4"			# M5StackのIPアドレス
$port=10000						# M5Stackの待ち受けポート番号
$path=Convert-Path .
$file = $path+"output.wav"					# 音声データを保存するファイル名

while ($TRUE)
{
	$data = Read-Host(">>")
	if ($data -eq "q") {break}
	$x=New-Object -ComObject SAPI.SpVoice
	$vs=New-Object -ComObject SAPI.SpFileStream
	$vs.Open($file,3)		# 変換した音声データを保存するファイルを開く
	$x.AudioOutputStream=$vs		# 変換した音声データをファイルに保存させる設定
      $x.Voice=$x.GetVoices().item(0)	# Japanese
#	$x.Voice=$x.GetVoices().item(1)	# English
	$x.Speak($data)				# 入力した文字列を喋らせる(データに変換してファイルに保存する)

	$vs.Close()					# ファイルを閉じる

	# ファイルからデータを取り出してバイト配列に入れる
	[Byte[]]$byte_data = Get-Content $file -AsByteStream

#	Write-Host $byte_data.Length

	$soc = New-Object System.Net.Sockets.tcpClient
	$soc.connect($ipaddress, $port)	# M5Stackに接続する
	$data_length=[byte[]] (@(0) * 4)	# wavファイルのサイズを保存する配列(4byteなので値範囲は0x0～0xFFFFFF)

	# wavファイルのサイズを配列に設定する
	$temp=$byte_data.Length			
	for($i=0;$i -lt 4;$i++){
		$data_length[$i]=[Math]::Floor($temp/[Math]::Pow(256,3-$i))
		$temp=$temp-( $data_length[$i]*[Math]::Pow(256,3-$i))
	}

	$soc.GetStream().Write($data_length, 0, 4)			# wavファイルのサイズをM5Stackに送信する
	$soc.GetStream().Write($byte_data, 0, $byte_data.Length)	# wavファイルのデータをM5Stackに送信する
}

$soc.close()					# M5Stackとの接続を閉じる

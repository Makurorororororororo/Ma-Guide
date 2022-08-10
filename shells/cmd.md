## Whoami
```
whoami /all
whoami /priv
whoami /groups
whoami /fqdn
whoami /user
```
## Checking OS info
```
systeminfo
```

## Dumps
### Wifi Dump
```
netsh wlan show profile Wi-Fi name key=clear
```

## Account management 
```
net user
net users /domain
net user {username} {password}
net localgroup administrators
net localgroup /domain
net localgroup Administrator {username} /add
```
## Netowrk
```
netstat 
netstat -an 
ipconfig {ip}
tracert {ip}
```

## connnect to shared folder 
```
net use \\IP address\IPC$ "" /u:""
net use \\192.168.1.101\IPC$ "" /u:""
```

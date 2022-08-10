## Port Scanning
### DNS
```
dig {URL}
```
### Nmap
```
nmap {IP}

# Scan a range of port numbers
nmap {IP} -p {port} - {port}

# Scan with version
nmap -sV {IP}

# Scan with Script
nmap -sC {IP}

# Scan UDP 
nmap -sU {IP}

# Scan and output to a file
nmap -oN {output file} {IP}

# Best scan
nmap -sC -sV {IP}
nmap -sC -sV -sU {IP}
nmap -sC -sV -oN {output file} {IP}
``` 

### Reconbot 
```
./reconbot {IP} 
./reconbot {IP} -p {Port}
./reconbot {IP} -w {wordlist}
```

### RustScan
```
rustscan -a {IP}
```

## Website
### Gobuster
```
gobuster dir -u {website URL} -w {word list location}
gobuster dir -u {website URL} -w {word list location} -t {threshold} -x txt,php -o {ouput file}

gobuster dir -u {URL} -w {wordlist} -q -n -e
```
#### wordlists
```
/usr/share/seclists/Discovery/Web-Content/directory-list-2.3-medium 
/usr/share/seclists/Discovery/Web-Content/common.txt
/usr/share/wordlists/dirb/common.txt
/usr/share/wordlists/dirb/big.txt
/usr/share/wordlists/dirb/indexes.txt
```

## OS
### Windows
```
Get-localgroup
Get-localgroupmember {GROUP}
net localgroup "group"
net user
whoami /priv
whoami /all
```
### Linux
```
whoami
id
cat /etc/groups
```
## NBTscan
```
nbtscan {IP}
```
> mainly to get netbios name

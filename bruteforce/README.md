## Wordlist
- Seclist: https://github.com/danielmiessler/SecLists
- rockyou: https://github.com/brannondorsey/naive-hashcat/releases/download/data/rockyou.txt

```
/usr/share/wordlists
/usr/share/seclists/Passwords/darkweb2017-top1000.txt
```

## John the Ripper
> Take note, john the ripper only accepts .hash type files. 

```
# converts the .zip file into a hash file 
john2zip {.zip file} > {.hash file}

# bruteforce
john --wordlist={wordlist} {.hash file}
john -show {.hash file}
```

## fcrackzip
```
fcrackzip -u -v -D -p {wordlist} {.zip}
```

## Hydra
```
# normal usage
hydra -L {name} -P {wordlist} {IP} smb

# website
hydra -l fergus -P /usr/share/wordlists/ 10.10.10.191 http-post-form "/admin/:tokenCSRF=c2cdfb24e13671a2f17f334e3cac54af6ee96f42&username=^USER^&password=^PASS^&save=:Username or password incorrect"

hydra -l admin -P 1000_common_passwords.txt -s 8090 -f 192.168.1.4 http-get /get_camera_params.cgi
```
> - take note there are SMB, SSH
> - need to find the error message for login 
> - use burpsuite

## Crackmapexec 
```
cme winrm {IP} -u {name} -p {wordlist/password}
```
> take note there are SSH, SMB, WINRM, ?, ?

## Hashcat 

https://github.com/frizb/Hashcat-Cheatsheet

> Hashcat ID
```
0 - MD5
100 - SHA1
900 - MD4
1000 - NTLM
1400 - SHA256
1700 - SHA256
11600 - 7-Zip
13000 - RAR5
13600 - WinZip
```
> In general hashes / windows

```
200 - bcrypt $2*$, Blowfish(Unix)
400 - sha256crypt $5$, SHA256(Unix)
500 - md5crypt $1$, MD5(Unix)
1800 - sha512crypt $6$, SHA512(Unix)
```
> Linux hashes (/etc/shadow)

```
hashcat.exe -a 0 -m {ID} {.hash/.txt file} {wordlist} -r rules\Insider-ProMAnagerHASdasdasdasd.txt
```
> general usage
```
13100 - Type 23 - $krb5tgs$23$
19600 - Type 17 - $krb5tgs$17$
19700 - Type 18 - $krb5tgs$18$
18200 - ASREP Type 23 - $krb5asrep$23$

hashcat -m 13100 -a 0 -w 4 {.hash file/.txt file} {wordlist}
```
> crack kerberoast hashes

```
echo -n "change" | hashcat --force --stdout -r /usr/share/hashcat/rules/{rule}.rule >> wordlist.txt | sort
```
> generate a wordlist out from the word "change" via rules.
```
InsiderPro-Hashmanager.rule
rockyou-3000.rule
best64.rule
```
> recommended rules
```
echo -n "change" | hashcat --force --stdout -r /usr/share/hashcat/rules/hybrid/append_d.rule  -r /usr/share/hashcat/rules/hybrid/append_d.rule  -r /usr/share/hashcat/rules/hybrid/append_d.rule  >> wordlist.txt | sort

echo "change" >> potential.txt
hashcat -a 6 potential.txt ?d?d?d --force --stdout > wordlist.txt
```
> generate a wordlist out from the word "change" and appending digit rules. E.g. change000 change032 change321





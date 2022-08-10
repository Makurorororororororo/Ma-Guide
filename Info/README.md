## Sensitive File areas
### Linux
```
# Commmon areas
.htpasswd
config.php
.htaccess
/etc/passwd
/etc/shadow
/etc/group
/etc/resolve.conf
/etc/motd
/etc/issues
~/.bash_history
/root/.bash_history
/home/{USERNAME}/.bash_history
$USER/.bash_history


# Logs
/etc/httpd/logs/acces_log 
/etc/httpd/logs/error_log 
/var/www/logs/access_log 
/var/www/logs/access.log 
/usr/local/apache/logs/access_ log 
/usr/local/apache/logs/access. log 
/var/log/apache/access_log 
/var/log/apache2/access_log 
/var/log/apache/access.log 
/var/log/apache2/access.log
/var/log/access_log
```
### Windows
```
C:\Users\{username}\APpData\Roaming\Microsoft\Windows\PowerShell\PSReadline\ConsoleHost_history.txt
```

## Registry 
```
# WDigest enable
HKLM\SYSTEM\CurrentControlSet\Control\SecurityProviders\WDigest\UseLogonCredential

# LSA secrets
HKLM\SECURITY\Policy\Secrets

# Autlogon 
HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon
```

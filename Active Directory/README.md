### Tools
```
import-module .\Microsoft.ActiveDirecotry.Manaagement.dll 
import-modoule .\ActiveDirectory\ActiveDirectory.psd1

import-module .\PowerView.ps1
. .\PowerView.ps1
```
### LDAP
```
ldapsearch -h {IP}
ldapsearch -h {IP} -x -s base namingcontexts
ldapsearch -h {IP} -x -b "{netbios}={domain},{netbios}={domain} | grep -i 
```
###  Domain Enmuration
```
# Get current Domain Controller name
echo %logonserver%
Get-NetDomainController
Get-ADDOmainController

# Get Domain name
Get-NetDomain
Get-ADDomain

# Domain SID
Get-DomainSID 
(Get-ADDomain).DomainSID

# Get Domain controller name from other domains
Get-NetDomainController -Domain {domain}
Get-ADDomainController -DomainNmae {domain} -Discover

# Get object from another domain
Get-NetDomain -Domain {Domain Name}
Get-ADDomain -Identity {Domain Name}
```
### Domain Policy
```
# Powerview only
Get-DomainPolicy

# useful information for passwords
(Get-DomainPolicy)."system access"

# get kerberos policy for golden ticket
(Get-DomainPolicy)."Kerberos Policy" 
```
### Domain User 
```
# PowerView
Get-NetUser
Get-NetUser | select cn
Get-NetUser -Username {name}
Get-UserProperty 
Get-UserProperty -Properties 

# Mircosoft Active Directory
Get-ADUser
Get-ADUser -Filter * -Properties *
Get-ADUser -Filter * -Properties * | select cn
Get-ADUser -Identity {name}

# Get the last set password, bad password count, logon count
Get-ADUser -Identity {name} - Properties *
Get-ADUser -Filter * -Properites * | select -First 1 | Get-Member -MemberType * Property  | select name
Get-ADUser -Filter * -Properties * | select name, @{expression ={[datetime]::formFileTime($__.pwdlastset)}}
```
### Domain Computers
Get all computers in the current domain
```
# PowerView
Get-NetComputer
Get-NetComputer -Operatingsytem "*Server 2016*"
Get-NetComputer -Ping
Get-Netcomputer -full data
Get-Netcomputer -Domain {domain}

# Mircosoft Active Directory
Get-ADComputer -Filter * | select name
Get-ADComputer -Filter 'OperatingSystem 0like "*Server 2016*"' -Properties OperatingSystem | select Name,OperatingSystem
Get-ADComputer -Filter * -Properties DNSHostName | %{Test-Connection} -Count 1 -ComputerName $_.DNSHostName}
Get-ADComputer -Filter * -Properties *
```
### Domain Groups
```
# Powerview
Get-NetGroup
Get-NetGroup -FullData
Get-NetGroup *admin*
Get-NetGroup -GroupName *admin*
Get-NetGroup 'admin' -FullData
Get-NetGroupMember -GroupName "Domain Admins" -Recurse
Get-NetGroupMember -GroupName "Enteprise Admins" -Domain {forest root}

# Use this command to get hidden accounts e.g., enterprise admin
Get-NetGroup -Domain {domain}
Get-Netgroup -GroupName *admin* -Domain {domain}

# Mircosoft Active Directory
Get-ADGroup -Filter * | select name
Get-ADGroup -Filter * -Properties *
Get-ADGroup -Filter 'Name -like "admin" ' | select name
Get-ADGroupMember -identity "domain admins"
Get-ADGroupMember -identity "Domain Admins" -Recursive


# Get group mmebership of a user
Get-NetGroup -UserName "{username}"
Get-ADPrincipalGroupMembership -Identity {username}

# list all local groups of a computer (requires admin)
Get-NetLocalGroup -ComputerName {computer name}
Get-NetLocalGroup -ComputerName {computer name} -ListGroups
Get-NetLocalGroup -ComputerName {computer name} -Recurse
```
### Get logged on users
> Requires administrator for all
```
# Get actively loged on users on the computer
Get-Netloggedon -ComputerName {computer name}

# Get locally loggged on users on the computer
Get-LoggedonLocal -ComputerName {computer name}

# Get last logged on user on a computer
Get-LastLoggedOn -ComputerName {computer name}
```
### Get Group Policy(GPO)
```
# Get GPO of the domain, PowerView
Get-NetGPO
Get-NetGPO | select displayname

# Get GPO of a computer, PowerView
Get-NetGPO -ComputerName (computer name)

# GroupPOlicy Module
Get-GPO -All 
Get-GPResultantSetOfPolicy -ReportType Html -Path {path} 

# get GPO of current machine
gpresult

# Get GPO whcihc use restricted groups
Get-NetGPOGroup

# Get users which are in a local group of a machine using GPO
Find-GPOComputerAdmin -Computername (computer name)
```
### Get Organization Unit (OU)
```
# PowerView
Get-NetOU
Get-NetOU -FullData

# Get GPO of the OU
gplink 
Get-NetGPO -GPOname "{OU Guid}"
Get-GPO -Guid {GUID}

# Microsoft Active Directory
Get-ADOrganizationalUnit -Filter * -Properties *
```
### Others
```
# Get SMB shares in the current domain
Invoke-ShareFinder -Verbose
Invoke-ShareFinder -Verbose -ExcludeStandard -ExcludePrint -ExcludeIPC

# Find sensitive information
Invoke-FileFinder -Verbose

# Get all fileservers of the domain
Get-NetFileServer
```

### ACL
```
# powerview
# Get ACL from the specificied object 
Get-objectACl -SamAccountName {username} -ResolveGUIDS

# get ACL associated with the specified prefix
Get-ObjectAcl -ADSprefix 'CN=Administrator,CN=Users' -Verbose

# Get ACL's accociated with the LDAP path
Get-ObjectAcl -ADSpath "LDAP://CN=Domain Admins,CN=Users,DC=dollarcor,DC=moneycorp,DC=local" -ResolveGUIDS -Verbose


# Microsoft Active Directory
(Get-Acl 'AD:\CN=Administrator,CN=Users,DC=dollarcorp,DC=money,DC=local').Access
```
ACE  (access control entries) = an individual permission or audit access over an object or group etc
ACL (access control list) = a group of ACE
DACL = defines teh permission of trutees (group/user) on a object
SACL = logs success and failure audit message when an object is access

ACE important properties
1. ObjectDN e.g. CN=student01,OU=studentmachine
2. IDentityReference e.g. Admin
3. ActiveDirectoryRights e.g. generic write
4. InhertiedObjectTypes e.g. all 
5. AccessControlType e.g. allow/deny
6. ObjectSID = SID of ObjectDN
#### Bloodhound
- Launch bloodhound 
- Download the collected data and upload it onto bloodhound
```
# On target machhine
. .\SharpHound.ps1
Invoke-BloodHound -CollectionMethod All 

# Avoid detectoin
Invoke-BloodHound -CollectionMethod All -Exclude DC 
```
##### Neo4j
- > provides sharphound a GUI
- > Default credentials: neo4j:neo4j
```
http://localhost:7474

# Windows
cd C:\neo4j\neo4j\bin
neo4j.bat install-service
neo4j.bat start 

Linux
sudo apt install neo4j
sudo apt install bloodhound
service neo4j start
```
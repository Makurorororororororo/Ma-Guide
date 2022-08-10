## Get Hashfile 
```
Get-FileHash .\{file} -Algorithm {hash type} | Format-List
```
hash type = SHA256, MD5 etc

## Find word / "grep" version of windows
```
select-string .\{file} -Pattern "{string}"

```
```
set-Content -Path .\{file} -Value "String"
```
```
Get-ChildItem {directory} -Filter *.log -Recurse | Select-String "{string}"
```
recursively find a string of all types of file in a directory. 

## Read/write a file 
```
Get-Content -Path .\{file}
Get-Content -Path .\{file} -TotalCount 5
(Get-Content -Path .\{file} -TotalCount 25)[-1]
```
```
Add-Content -Path .\{file} -Value "{string}}"
```

## Get info about account
```
Get-ADUser -Identity {name} -Properties *
net user "{name}"
```

## Enable accounts
```
Enable-LocalUser -Name "{name}"
Enable-ADAccount -Identity "{name/Distinguished Name}"
```

## Registry
> For setting registry path: {short form of each HKEY}:\PATH
> E.g. (HKEY_LOCAL_MACHINE) HKLM:\SOFTWARE\Windows\CurrentVersion
#### Edit registry 
```
Set-Itemproperty -path {path} -Name '{name of property you want to edit}' -value {value}
```
#### Add new property
```
New-ItemProperty -Path '{HKLM:\registry path}' -name "{name}" -PropertyType {type} -value "{value}" 
```

> String: Specifies a null-terminated string. Equivalent to REG_SZ.
ExpandString: Specifies a null-terminated string that contains unexpanded references to environment variables that are expanded when the value is retrieved. Equivalent to REG_EXPAND_SZ.
Binary: Specifies binary data in any form. Equivalent to REG_BINARY.
DWord: Specifies a 32-bit binary number. Equivalent to REG_DWORD.
MultiString: Specifies an array of null-terminated strings terminated by two null characters. Equivalent to REG_MULTI_SZ.
Qword: Specifies a 64-bit binary number. Equivalent to REG_QWORD.
Unknown: Indicates an unsupported registry data type, such as REG_RESOURCE_LIST.


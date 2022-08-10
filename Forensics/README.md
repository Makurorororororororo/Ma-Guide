## oledump
Used to read a "suspected" word/excel/ppt macro file. Used for streaming.
```
python3 oledump.py {file} 
python3 oledump.py {file} -s {stream}
python3 oledump.py {file} -s {stream} -S 
```
-s = select
-S = show as String

## olevba
Used to read a "suspected" word/excel/ppt macro file. Better version then oledump.
```
pyhton3 olevba.py {file} 
```

## Volality
Used to read a memory dump / .dmp file
```
python3 vol.py -f {file}
```
https://github.com/volatilityfoundation/volatility

```
python3 vol.py imageinfo -f {file}
python3 vol.py kdbgscan -f {file}
```
Discover Profiles
https://book.hacktricks.xyz/forensics/basic-forensic-methodology/memory-dump-analysis/volatility-examples

taskkill /F /IM Urbexs-qt.exe
mkdir "%USERPROFILE%"\Desktop\urbexsbackup
cd "%USERPROFILE%"\Urbexs\
del -r smsgStore
del -r smsgDB
del *.log
del smsg.ini
del blk*
del -r database
del -r txleveldb
del peers.dat
del mncache.dat
xcopy /E .\* "%USERPROFILE%"\Desktop\urbexsbackup

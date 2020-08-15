@echo off 
echo 正在打开游戏，请稍等...... 
taskkill /f /im RemoteDesktopClientD.exe
start "" "D:\CaptureStream\binclientnew\RemoteDesktopClientD.exe" 2
echo 打开完成！ 
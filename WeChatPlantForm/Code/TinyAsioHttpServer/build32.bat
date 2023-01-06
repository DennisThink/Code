mkdir Build32Bat
cd Build32Bat
cmake ..
MSBuild.exe TinyAsioHttpServer.sln -property:Configuration=Debug
cd ..
pause

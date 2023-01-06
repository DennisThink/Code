mkdir Build64Bat
cd Build64Bat
cmake .. -G "Visual Studio 16 2019 Win64"
MSBuild.exe TinyWeatherService.sln -property:Configuration=Debug
cd ..
pause

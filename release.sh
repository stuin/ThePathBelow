files="src/main.cpp src/Skyrmion/*.cpp"
options="-pthread -O3 -std=c++17 -Wall -fpermissive"
windows_libs="-static -DSFML_STATIC -mwindows -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype"
linux_libs="-lsfml-graphics -lsfml-window -lsfml-system -lX11"

output="ThePathBelow"

windows_cmd="x86_64-w64-mingw32-g++ $files -o $output.exe $options $windows_libs"
linux_cmd="g++ $files -o $output.out $options $linux_libs"

echo $windows_cmd
$windows_cmd

echo $linux_cmd
$linux_cmd

echo "Done, Creating zip"
mv res/settings.json dev_settings.json
cp res/default_settings.json res/settings.json
zip -r "$output.zip" "$output.*" res/
mv dev_settings.json res/settings.json


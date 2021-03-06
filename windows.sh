files="src/main.cpp src/Skyrmion/GridMaker.cpp src/Skyrmion/Node.cpp src/Skyrmion/UpdateList.cpp  src/Skyrmion/LightMap.cpp"
options="-pthread -O3 -std=c++17 -Wall -fpermissive -mwindows -static -DSFML_STATIC"
libs="-lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype"

output="ThePathBelow"

cmd="x86_64-w64-mingw32-g++ $files -o $output.exe $options $libs"

echo $cmd
$cmd

echo "Done, Creating zip"
zip -r ThePathBelow.zip ThePathBelow.* res/


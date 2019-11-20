
map: main.cpp src/shapefile.cpp src/record.cpp
	emcc main.cpp src/shapefile.cpp src/record.cpp -std=c++1z -s FULL_ES3=1 -o index.html

clean:
	rm index.html index.js index.wasm


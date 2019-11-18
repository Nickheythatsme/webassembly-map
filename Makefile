
map: main.cpp src/shapefile.cpp
	emcc main.cpp src/shapefile.cpp -std=c++1z -o index.html

clean:
	rm index.html index.js index.wasm


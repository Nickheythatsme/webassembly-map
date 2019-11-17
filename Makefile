
map: main.cpp
	emcc main.cpp -std=c++1z -o index.html

clean:
	rm index.html index.js index.wasm


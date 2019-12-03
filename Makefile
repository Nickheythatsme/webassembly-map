default: map

map: main.cpp src/shapefile.cpp src/record.cpp
	emcc main.cpp src/shapefile.cpp src/record.cpp --preload-file data/Neighborhoods_Regions.shp -std=c++1z -s FULL_ES3=1 -o index.html

sdl2: sdl2_example.cpp
	emcc $@ -s USE_SDL=2 -s LEGACY_GL_EMULATION=1 -o sdl2.html

clean:
	rm -f index.*
	rm -f sdl2glshader sdl2.*


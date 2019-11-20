
map: main.cpp src/shapefile.cpp src/record.cpp
	emcc main.cpp src/shapefile.cpp src/record.cpp src/shape_utils.cpp --preload-file data/Neighborhoods_Regions.shp -std=c++1z -s FULL_ES3=1 -o index.html

clean:
	rm index.*
	rm a.out.*


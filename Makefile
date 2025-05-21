all:
	git clone https://github.com/raysan5/raylib.git
	cd raylib && mkdir build && cd build && emcmake cmake .. -DBUILD_EXAMPLES=OFF -DPLATFORM=Web && make

	emcc -o dist/index.html src/main.cpp \
	  -O2 -Wall -std=c++11 \
	  -Iraylib/src -Lraylib/build -lraylib \
	  -s USE_GLFW=3 \
	  -s ASYNCIFY \
	  -s FORCE_FILESYSTEM=1 \
	  -s TOTAL_MEMORY=268435456 \
	  --preload-file assets \
	  -s ALLOW_MEMORY_GROWTH=1 \
	  -s EXPORTED_FUNCTIONS='["_main"]' \
	  -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'

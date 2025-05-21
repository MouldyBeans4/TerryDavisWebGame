all:
	emcc src/main.cpp -o dist/index.html \
	  -O2 -s USE_SDL=2 -s ASYNCIFY \
	  --preload-file assets \
	  -s ALLOW_MEMORY_GROWTH=1 \
	  -s EXPORTED_FUNCTIONS='["_main"]' \
	  -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'
default_target: all

clean:
	rm -f MiniEngine

all: clean
	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	make -C build
	ln -s ./build/MiniEngine .

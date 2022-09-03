

debug:
	cmake -E make_directory $(CURDIR)/debug
	cmake -S $(CURDIR) -B $(CURDIR)/debug -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTING=ON
	cmake --build $(CURDIR)/debug --parallel

utest: debug
	./debug/test/testBin
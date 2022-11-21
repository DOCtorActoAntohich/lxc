.PHONY: default
default:
	@echo Choose target

.PHONY: configure
configure: clean
	@cmake \
		--no-warn-unused-cli \
		-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
		-DCMAKE_BUILD_TYPE:STRING=Release \
		-DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc \
		-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
		-S. \
		-B./build \
		-G Ninja

.PHONY: build
build:
	cmake --build \
		./build \
		--config Release \
		--target all \
		--

.PHONY: run
run:
	sudo ./bin/mogringe

.PHONY: clean
clean:
	rm -rf build
	rm -rf bin
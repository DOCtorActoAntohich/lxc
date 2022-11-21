.PHONY: default
default:
	@echo Choose target

.PHONY: configure
configure:
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
build: configure
	cmake --build \
		./build \
		--config Release \
		--target all \
		--

.PHONY: run
run: build
	sudo ./bin/mogringe

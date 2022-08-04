binary := team-formation-generator

build:
	@echo building ${binary}
	@ g++ ${binary}.cpp -o ${binary}.o

run: build
	@echo running ${binary}
	@echo "--------------"
	@ ./${binary}.o

clean:
	@echo removing binaries
	@ rm -rf *.o

all: build run clean

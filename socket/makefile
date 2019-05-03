all : ./src

./src : 
	mkdir -p bin
	mkdir -p lib
	mkdir -p inc
	mkdir -p obj
	$(MAKE) -C ./src

clean:
	rm -rf ./obj  ./bin ./inc ./lib

.PHONY : ./src clean

.PHONY : test

test : ./bin/server_tcp ./bin/server_udp ./bin/client_tcp ./bin/client_udp
	bash -c "export ld_library_path=./lib"
	bash -c "touch test.txt"
	bash -c "./bin/server_udp >> test.txt &"
	bash -c "./bin/server_tcp >> test.txt &"
	bash -c "./bin/client_udp >> test.txt "
	bash -c "./bin/client_tcp >> test.txt "
	diff -u golden.txt test.txt
	rm -rf test.txt


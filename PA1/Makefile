all: bin/pa1.out
	./bin/pa1.out -z 9 -s 27 -a s
	./bin/pa1.out -z 9 -s 27 -a i
	./bin/pa1.out -z 9 -s 27 -a q
	./bin/pa1.out -z 9 -s 27 -a q3
	./bin/pa1.out -z 9 -s 27 -a qi
	./bin/pa1.out -z 9 -s 27 -a q3i
	./bin/pa1.out -z 9 -s 27 -a h
	./bin/pa1.out -z 9 -s 27 -a rs
	./bin/pa1.out -z 81 -s 17 -a s
	./bin/pa1.out -z 81 -s 17 -a i
	./bin/pa1.out -z 81 -s 17 -a q
	./bin/pa1.out -z 81 -s 17 -a q3
	./bin/pa1.out -z 81 -s 17 -a qi
	./bin/pa1.out -z 81 -s 17 -a q3i
	./bin/pa1.out -z 81 -s 17 -a h
	./bin/pa1.out -z 81 -s 17 -a rs
	./bin/pa1.out -z 448 -s 15 -a s
	./bin/pa1.out -z 448 -s 15 -a i
	./bin/pa1.out -z 448 -s 15 -a q
	./bin/pa1.out -z 448 -s 15 -a q3
	./bin/pa1.out -z 448 -s 15 -a qi
	./bin/pa1.out -z 448 -s 15 -a q3i
	./bin/pa1.out -z 448 -s 15 -a h
	./bin/pa1.out -z 448 -s 15 -a rs
	./bin/pa1.out -z 4803 -s 34 -a s
	./bin/pa1.out -z 4803 -s 34 -a i
	./bin/pa1.out -z 4803 -s 34 -a q
	./bin/pa1.out -z 4803 -s 34 -a q3
	./bin/pa1.out -z 4803 -s 34 -a qi
	./bin/pa1.out -z 4803 -s 34 -a q3i
	./bin/pa1.out -z 4803 -s 34 -a h
	./bin/pa1.out -z 4803 -s 34 -a rs
	./bin/pa1.out -z 19097 -s 25 -a s
	./bin/pa1.out -z 19097 -s 25 -a i
	./bin/pa1.out -z 19097 -s 25 -a q
	./bin/pa1.out -z 19097 -s 25 -a q3
	./bin/pa1.out -z 19097 -s 25 -a qi
	./bin/pa1.out -z 19097 -s 25 -a q3i
	./bin/pa1.out -z 19097 -s 25 -a h
	./bin/pa1.out -z 19097 -s 25 -a rs

bin/pa1.out: src/pa1.c
	@mkdir -p bin
	gcc -Wall -g src/pa1.c -o bin/pa1.out

clean:
	rm -rf bin/*

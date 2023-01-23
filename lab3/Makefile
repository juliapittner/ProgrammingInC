all: createThreads parallel parallel2 parallel3

createThreads: createThreads.c
	gcc -pthread -o createThreads createThreads.c

parallel: parallel.c
	gcc -pthread -o parallel parallel.c

parallel2: parallel2.c
	gcc -pthread -o parallel2 parallel2.c

parallel3: parallel3.c
	gcc -pthread -o parallel3 parallel3.c
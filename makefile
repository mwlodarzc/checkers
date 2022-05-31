TRGDIR=./
OBJ=./obj
FLAGS= -Wall -pedantic -std=gnu++2a -g -iquote inc

${TRGDIR}/a.out: ${OBJ} ${OBJ}/main.o ${OBJ}/CheckerBoardSquare.o ${OBJ}/CheckerBoard.o
	g++ -o ${TRGDIR}/a.out ${OBJ}/main.o ${OBJ}/CheckerBoardSquare.o ${OBJ}/CheckerBoard.o
	
${OBJ}:
	mkdir ${OBJ}

${OBJ}/main.o: src/main.cpp 
	g++ -c ${FLAGS} -o ${OBJ}/main.o src/main.cpp

${OBJ}/CheckerBoardSquare.o: src/CheckerBoardSquare.cpp 
	g++ -c ${FLAGS} -o ${OBJ}/CheckerBoardSquare.o src/CheckerBoardSquare.cpp 

${OBJ}/CheckerBoard.o: src/CheckerBoard.cpp 
	g++ -c ${FLAGS} -o ${OBJ}/CheckerBoard.o src/CheckerBoard.cpp 

clear:
	rm -r ${OBJ} a.out

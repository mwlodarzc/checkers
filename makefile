TRGDIR=./
OBJ=./obj
FLAGS= -Wall -pedantic -std=gnu++2a -g -iquote inc
WXINC= `wx-config --cppflags --libs`
${TRGDIR}/a.out: ${OBJ} ${OBJ}/main.o ${OBJ}/CheckerBoard.o ${OBJ}/Square.o ${OBJ}/Piece.o
	g++ -o ${TRGDIR}/a.out ${OBJ}/main.o ${OBJ}/CheckerBoard.o ${OBJ}/Square.o ${OBJ}/Piece.o ${WXINC}
	
${OBJ}:
	mkdir ${OBJ}

${OBJ}/main.o: src/main.cpp 
	g++ -c ${FLAGS} -o ${OBJ}/main.o src/main.cpp ${WXINC}

${OBJ}/CheckerBoard.o: src/CheckerBoard.cpp 
	g++ -c ${FLAGS} -o ${OBJ}/CheckerBoard.o src/CheckerBoard.cpp ${WXINC}

${OBJ}/Square.o: src/Square.cpp 
	g++ -c ${FLAGS} -o ${OBJ}/Square.o src/Square.cpp ${WXINC}

${OBJ}/Piece.o: src/Piece.cpp 
	g++ -c ${FLAGS} -o ${OBJ}/Piece.o src/Piece.cpp ${WXINC}

# ${OBJ}/GameWindow.o: src/GameWindow.cpp 
# 	g++ -c ${FLAGS} -o ${OBJ}/GameWindow.o src/GameWindow.cpp ${WXINC}

# ${OBJ}/CheckerBoard.o: src/CheckerBoard.cpp 
# 	g++ -c ${FLAGS} -o ${OBJ}/CheckerBoard.o src/CheckerBoard.cpp 

clear:
	rm -r ${OBJ} a.out

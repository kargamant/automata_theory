all:
	flex -+ rules.l
	g++ -o main lex.yy.cc ../Recognizer/Recognizer.cpp FlexRecognizer.cpp -lfl

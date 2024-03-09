default: scanner cmos

scanner: lex.yy.c
	g++ lex.yy.c -o scanner

lex.yy.c: cmos.l
	flex cmos.l

cmos: cmos.cpp
	g++ -g cmos.cpp -o cmos


shell:
	chmod +x PlagarismDetector && ./PlagarismDetector /Examples
	./cmos tokens.txt 


clean:
	rm -f lex.yy.c scanner tokens.txt scanner_out.txt cmos
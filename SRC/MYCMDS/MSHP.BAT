del shperrs.err				

iff "%user"=="ROBERT" .OR. "%user"=="VLADDRAK" .OR. "%user"=="RICHARD" .OR. "%user"=="TOKS" then
	iff "%user"=="ROBERT" then
		shpmke2w -a -w -o 3 -c -ps -p ..\shapes\
	else
		shpmke2w -a -w -o 3 -ps
	endiff
else
	shpmke2w -a -o 3
endiff

	

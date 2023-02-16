default:
	gcc -fsyntax-only -fsanitize=undefined -Wall -Wextra -lm *.c -std=c2x

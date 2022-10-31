shell: a.out
	./a.out

a.out: shell.c
	gcc shell.c

ls: ls.c
	gcc ls.c -o ls

mkdir: mkdir.c
	gcc mkdir.c -o mkdir

date: date.c
	gcc date.c -o date

rm: rm.c
	gcc rm.c -o rm

cat: cat.c
	gcc cat.c -o cat

first.run: first.exe
	./first
	rm ./first

first.exe: first_one.c 
	gcc first_one.c -o first
	
clean:
	rm ./first
	






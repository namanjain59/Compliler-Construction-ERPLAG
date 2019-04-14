# Batch Number 80
# Naman Jain 2014A7PS100P
# Saksham Nagar 2014A7PS040P

output: driver.o
	gcc -g  -o compiler  driver.o -lm

driver.o: driver.c
	gcc -c -g driver.c -lm 
clean:
	rm *.o
	rm driver

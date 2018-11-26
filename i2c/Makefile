all: get_temp get_press

i2c_temp.o: i2c_temp.c i2c_api.h MPU9255.h
	gcc -c i2c_temp.c -O2

i2c_api.o: i2c_api.c i2c_api.h MPU9255.h
	gcc -c i2c_api.c -O2

i2c_press.o: i2c_press.c i2c_api.h MPU9255.h
	gcc -c i2c_press.c -O2

get_temp: i2c_temp.o i2c_api.o
	gcc -o get_temp i2c_temp.o i2c_api.o

get_press: i2c_press.o i2c_api.o
	gcc -o get_press i2c_press.o i2c_api.o -lm


clean:
	rm -rf *.o get_temp get_press

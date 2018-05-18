all: temperature_monitor

i2c_temp.o: i2c_temp.c i2c_api.h MPU9255.h server_api.h
	gcc -c i2c_temp.c -O2

i2c_api.o: i2c_api.c i2c_api.h MPU9255.h
	gcc -c i2c_api.c -O2

server_api.o: server_api.c server_api.h
	gcc -c server_api.c -O2

temperature_monitor: i2c_temp.o i2c_api.o server_api.o
	gcc -o temperature_monitor i2c_temp.o i2c_api.o server_api.o

clean:
	rm -rf *.o temperature_monitor

all: upload

clean:
	rm -f *.elf *.hex

compile: 04.08.ino
	../../arduino compile --fqbn arduino:avr:uno ../04.08

upload: compile
	../../arduino upload -p /dev/ttyACM0 --fqbn arduino:avr:uno ../04.08

attach:
	screen /dev/ttyACM0 115200

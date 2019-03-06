all: upload

clean:
	rm -f *.elf *.hex

compile: 02.25.ino
	../../arduino compile --fqbn arduino:avr:uno ../02.25

upload: compile
	../../arduino upload -p /dev/ttyACM0 --fqbn arduino:avr:uno ../02.25

attach:
	screen /dev/ttyACM0 115200

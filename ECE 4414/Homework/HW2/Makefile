all:
	@echo "Choose an option"

Ex1: Ex1/Ex1.ino
	../../arduino compile --fqbn arduino:avr:uno Ex1
	../../arduino upload -p /dev/ttyACM0 --fqbn arduino:avr:uno Ex1
	screen /dev/ttyACM0 115200

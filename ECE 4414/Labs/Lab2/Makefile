all:
	@echo "Choose an option"

Ex1: Ex1/Ex1.ino
	../../arduino compile --fqbn arduino:avr:uno Ex1
	../../arduino upload -p /dev/ttyACM0 --fqbn arduino:avr:uno Ex1
	screen /dev/ttyACM0 115200

Ex2: Ex2/Ex2.ino
	../../arduino compile --fqbn arduino:avr:uno Ex2
	../../arduino upload -p /dev/ttyACM0 --fqbn arduino:avr:uno Ex2

Ex3: Ex3/Ex3.ino
	../../arduino compile --fqbn arduino:avr:uno Ex3
	../../arduino upload -p /dev/ttyACM0 --fqbn arduino:avr:uno Ex3
	screen /dev/ttyACM0 115200

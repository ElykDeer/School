'setup:
	../arduino lib install "WaveHC"

setup-test:
	../arduino compile --fqbn arduino:avr:uno setup
	../arduino upload -p /dev/ttyACM0 --fqbn arduino:avr:uno setup
	screen /dev/ttyACM0 115200

example:
	../arduino compile --fqbn arduino:avr:uno example
	../arduino upload -p /dev/ttyACM0 --fqbn arduino:avr:uno example
	screen /dev/ttyACM0 115200

Ver1: Ver1/Ver1.ino
	../arduino compile --fqbn arduino:avr:uno Ver1
	../arduino upload -p /dev/ttyACM0 --fqbn arduino:avr:uno Ver1
	screen /dev/ttyACM0 115200

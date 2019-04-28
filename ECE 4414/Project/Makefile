setup:
	../arduino lib install "WaveHC"

setup-test:
	../arduino compile --fqbn arduino:avr:uno setup
	../arduino upload -p /dev/ttyACM0 --fqbn arduino:avr:uno setup
	screen /dev/ttyACM0 115200

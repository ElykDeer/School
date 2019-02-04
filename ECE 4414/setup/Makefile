all:
	@echo "Choose an option"

setup:
	sudo usermod -aG dialout kyle
	sudo usermod -aG tty kyle
	wget https://downloads.arduino.cc/arduino-cli/arduino-cli-latest-linux64.tar.bz2
	tar -xf arduino-cli-latest-linux64.tar.bz2
	rm arduino-cli-latest-linux64.tar.bz2
	mv arduino* ../arduino
	../arduino core update-index
	../arduino core install arduino:avr

test:
	../arduino compile --fqbn arduino:avr:uno ../setup
	../arduino upload -p /dev/ttyACM0 --fqbn arduino:avr:uno ../setup


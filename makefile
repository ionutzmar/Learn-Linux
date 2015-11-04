build:
	sudo gcc moveMouse.c -o "moveMouse"  -Wall
run:
	sudo ./moveMouse
detectMouse:
	sudo gcc mouseCoordinates.c -o "letsGetTheCoordinates" -Wall
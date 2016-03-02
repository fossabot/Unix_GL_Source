build:
	g++ -o controller controller.cpp `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

python-setup-export:
	sudo pip install Pillow &&  sudo pip install images2gif && brew install ffmpeg

movie:
	cd ../screenshots/ && ffmpeg -framerate 60 -i shot_%04d.png -c:v libx264 -r 60 ../exports/out.mp4

gif:
	cd ../screenshots/ && convert -delay 10 -loop 0 *.png ../exports/animation.gif

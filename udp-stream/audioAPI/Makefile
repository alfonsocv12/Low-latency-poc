LINUX_LIBS = -D__LINUX_ALSA__ -lasound -lpthread

compile-main:
	g++ $(LINUX_LIBS) -std=c++14 \
		./main.cpp ./lib/rtaudio-5.2.0/RtAudio.cpp \
		-Ilib/rtaudio-5.2.0 \
		-o bin/main 

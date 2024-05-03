LINUX_LIBS = -D__LINUX_ALSA__ -lasound -lpthread
MACOS_LIBS = -D__MACOSX_CORE__ -framework CoreAudio -framework CoreFoundation

compile-linux:
	g++ $(LINUX_LIBS) -std=c++14 \
		./main.cpp ./lib/rtaudio-5.2.0/RtAudio.cpp \
		-Ilib/rtaudio-5.2.0 \
		-o bin/main 
compile-macos:
	g++ $(MACOS_LIBS) -std=c++14 \
		./main.cpp ./udpSend/udpSend.cpp ./lib/rtaudio-5.2.0/RtAudio.cpp \
		-Ilib/rtaudio-5.2.0 \
		-o bin/main 

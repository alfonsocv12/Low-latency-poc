MACOS_LIBS = -D__MACOSX_CORE__ -framework CoreAudio -framework CoreFoundation
WINDOS_LIBS = -D__WINDOWS_ASIO__ -lasound -lpthread

compile-windows:
	g++ -std=c++14 \
		./main.cpp ../audioClient/lib/rtaudio-5.2.0/RtAudio.cpp \
		-I../audioClient/lib/rtaudio-5.2.0 \
		-o bin/server

compile-macos:
	g++ $(MACOS_LIBS) -std=c++14 \
		./main.cpp ../audioClient/lib/rtaudio-5.2.0/RtAudio.cpp \
		-I../audioClient/lib/rtaudio-5.2.0 \
		-o bin/server

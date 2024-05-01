MACOS_LIBS = -D__MACOSX_CORE__ -framework CoreAudio -framework CoreFoundation

compile-macos:
	g++ $(MACOS_LIBS) -std=c++14 \
		./main.cpp ../audioClient/lib/rtaudio-5.2.0/RtAudio.cpp \
		-I../audioClient/lib/rtaudio-5.2.0 \
		-o bin/server

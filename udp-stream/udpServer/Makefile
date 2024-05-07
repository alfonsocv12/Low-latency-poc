MACOS_LIBS = -D__MACOSX_CORE__ -framework CoreAudio -framework CoreFoundation
WINDOWS_LIBS = -D__WINDOWS_ASIO__ -Iinclude -lasound -lole32

RT_AUDIO_LIB = ../audioClient/lib/rtaudio-5.2.0

compile-windows:
	g++ $(WINDOWS_LIBS) -std=c++14 \
		./main.cpp $(RT_AUDIO_LIB)/RtAudio.cpp \
		$(RT_AUDIO_LIB)/asio.cpp $(RT_AUDIO_LIB)/audioprobe.cpp \
		$(RT_AUDIO_LIB)/asiolist.cpp $(RT_AUDIO_LIB)/asiodrivers.cpp $(RT_AUDIO_LIB)/iasiothiscallresolver.cpp \
		-I../audioClient/lib/rtaudio-5.2.0 \
		-o bin/server

compile-macos:
	g++ $(MACOS_LIBS) -std=c++14 \
		./main.cpp ../audioClient/lib/rtaudio-5.2.0/RtAudio.cpp \
		-I../audioClient/lib/rtaudio-5.2.0 \
		-o bin/server

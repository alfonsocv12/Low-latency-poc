MACOS_LIBS = -D__MACOSX_CORE__ -framework CoreAudio -framework CoreFoundation
WINDOWS_LIBS = -D__WINDOWS_DS -lole32 -lwinmm -ldsound -lws2_32

RT_AUDIO_LIB = ../audioClient/lib/rtaudio-5.2.0
RT_AUDIO_LIB_WIN32 = ..\audioClient\lib\rtaudio-5.2.0

compile-windows:
	g++ $(WINDOWS_LIBS) -std=c++14 \
		.\main.cpp $(RT_AUDIO_LIB_WIN32)\RtAudio.cpp -L "$(RT_AUDIO_LIB_WIN32)" \
		-o bin/server

compile-macos:
	g++ $(MACOS_LIBS) -std=c++14 \
		./main.cpp ../audioClient/lib/rtaudio-5.2.0/RtAudio.cpp \
		-I../audioClient/lib/rtaudio-5.2.0 \
		-o bin/server

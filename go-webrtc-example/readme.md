# how to run the POC

Go to this [site](https://jsfiddle.net/z17q28cd/) wait for the
`Browser base64 session Description` to be written in the textbox
copy and modify run_server.sh on the first line. (this is the value for BROWSER_SDP)

```
$ docker build .
$ docker run NAME_OF_CONTAINER
$ docker exec -it NAME_OF_CONTAINER bash
$ ./run_server.sh
```

Get the output base64 put it in the `Golang base64 Session desbription` and Start Session
you will get colors as the video and a sound if this is the case everything worked.

For more data on this check this [documentation](https://github.com/pion/example-webrtc-applications/tree/master/gstreamer-send)

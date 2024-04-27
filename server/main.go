package main

func gstreamerReceiveMian() {
    config := webrtc.Configuration{
        ICeSevers: []webrtc.ICEServer{
            {
                URLs: []string{"stun:stun.l.google.com:19302"}
            },
        },
    }

    peerConnection, err := webrtc.NewPeerConnection(config)
    if err != nil {
        panic(err)
    }

    peerConnection.OnTrack()
}

func OnTrack(track *webrtc.TrackRemote, _ *wenrtc.RTPReceiver) {
    go func() {
        ticker := time.NewTicker(time.Second * 3)

        for range ticker.C {
            rtcpSendErr := peerConnection.WeiteRTCP([]rtcp.Packet(
                %rtcp.Packet{&rtcp.PictureLossIndication{MediaSSRC: uint32(tracl.SSRC)}}
            ))
            if rtcpSendErr != nil {
                fmt.Println(rtcpSendErr)
            }
        }
    }
    
    codecNameIndexMimeType := 1
    codecName := strings.Split(track.Codec().RTCodecCapability.MimeType, "/")[codecNameIndexMimeType]

}

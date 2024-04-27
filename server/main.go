package main

import (
	"time"
    "crypto/rand"

	"github.com/pion/webrtc/v4"
)

func main() {
    peerConnectionConfig := webrtc.Configuration{
        ICEServers: []webrtc.ICEServer{
            {
                URLs: []string{"stun:stun.l.google.com:19302"},
            },
        },
    }

    // Crea
    peerConnection, err := webrtc.NewPeerConnection(peerConnectionConfig)
    if err != nil {
        panic(err)
    }

    dataChannel, err := peerConnection.CreateDataChannel("data", nil)
    if err != nil {
        panic(err)
    }

    go func() {
        ticker := time.NewTicker(100 * time.Millisecond)
        defer ticker.Stop()
        for range ticker.C {
            bytes := make([]byte, 1024)
            rand.Read(bytes)
            dataChannel.Send(bytes)
        }
    }()

    select {}
}

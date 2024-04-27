package main

import (
    "fmt"
    "time"

    "github.com/pion/webrtc/v4"
)

func main() {
    // Set up signaling mechanism for peer connection

    // Create a new WebRTC peer connection configuration
    config := webrtc.Configuration{        
        ICEServers: []webrtc.ICEServer{
            {
            },
        },
    }

    // Create a new WebRTC peer connection
    peerConnection, err := webrtc.NewPeerConnection(config)
    if err != nil {
        panic(err)
    }
    defer peerConnection.Close()

    // Set up a listener for the data channel
    peerConnection.OnDataChannel(func(dc *webrtc.DataChannel) {
        dc.OnMessage(func(msg webrtc.DataChannelMessage) {
            // Calculate delay and print it out
            msgSting := string(msg.Data)
            data, _ := time.Parse(time.RFC3339, msgSting)
            if data.IsZero() {
                fmt.Println("Invalid time")
                return
            }  
            fmt.Printf("Delay: %v\n", time.Since(data))
        })
    })

    // Block indefinitely
    select {}
}

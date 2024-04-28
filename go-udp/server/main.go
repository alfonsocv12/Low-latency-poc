package main

import (
	"encoding/binary"
	"fmt"
	"net"
	"time"
)

func main() {
    localAddr, err := net.ResolveUDPAddr("udp", ":8080")
    if err != nil {
        fmt.Println("Error resolving local address:", err)
        return
    }

    conn, err := net.ListenUDP("udp", localAddr)
    if err != nil {
        fmt.Println("Error listening:", err)
        return
    }
    defer conn.Close()

    fmt.Println("Listening for incoming UDP messages on", localAddr)

    go func() {
        for {
            buffer := make([]byte, 8)

            _, _, err := conn.ReadFromUDP(buffer)
            receivedTime := time.Now()
            if err != nil {
                fmt.Println("Error reading:", err)
                continue
            }

            sendTime := time.Unix(0, int64(binary.LittleEndian.Uint64(buffer)))

            fmt.Printf(
                "Received read message dealta %s Received %s Send %s\n", 
                receivedTime.Sub(sendTime).String(),
                receivedTime.Format("2006-01-02 15:04:05.000"),
                sendTime.Format("2006-01-02 15:04:05.000"),
            )
        }
    }()

    select {}
}

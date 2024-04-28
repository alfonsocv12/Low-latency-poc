package main

import (
	"encoding/binary"
	"fmt"
	"net"
	"time"
)

func main() {
    remoteAddr, err := net.ResolveUDPAddr("udp", "127.0.0.1:8080")
    if err != nil {
        fmt.Println("Error resolving remote address:", err)
        return
    }

    conn, err := net.ListenUDP("udp", nil)
    if err != nil {
        fmt.Println("Error dialing:", err)
        return
    }
    defer conn.Close()
    
    // Send current time to the remote peer
    for true {
        messageBuf := make([]byte, 8)
        binary.LittleEndian.PutUint64(messageBuf, uint64(time.Now().UnixNano()))
        _, err = conn.WriteToUDP(messageBuf, remoteAddr)
        if err != nil {
            fmt.Println("Error sending message:", err)
            return
        }
    }
}

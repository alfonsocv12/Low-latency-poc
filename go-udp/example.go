package main

import (
    "fmt"
    "net"
)

func main() {
    // Get the local UDP address
    localAddr, err := net.ResolveUDPAddr("udp", ":8080")
    if err != nil {
        fmt.Println("Error resolving local address:", err)
        return
    }

    // Create a UDP listener
    conn, err := net.ListenUDP("udp", localAddr)
    if err != nil {
        fmt.Println("Error listening:", err)
        return
    }
    defer conn.Close()

    fmt.Println("Listening for incoming UDP messages on", localAddr)

    // Start a goroutine to handle incoming messages
    go func() {
        for {
            // Buffer to hold incoming data
            buffer := make([]byte, 1024)

            // Read data from the connection
            n, addr, err := conn.ReadFromUDP(buffer) 

            if err != nil {
                fmt.Println("Error reading:", err)
                continue
            }
    
            fmt.Printf("Received message from %s: %s\n", addr, string(buffer[:n]))
        }
    }()

    // Get the remote UDP address
    remoteAddr, err := net.ResolveUDPAddr("udp", "127.0.0.1:8080")
    if err != nil {
        fmt.Println("Error resolving remote address:", err)
        return
    }

    // Send a message to the remote peer
    message := []byte("Hello from peer 1")
    _, err = conn.WriteToUDP(message, remoteAddr)
    if err != nil {
        fmt.Println("Error sending message:", err)
        return
    }

    fmt.Println("Message sent to remote peer")
    
    // Infinite loop to keep the program running
    select {}
}

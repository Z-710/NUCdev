import socket
import sys

def scan_port(ip, port):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(0.1)  # Setting the default timeout to 100ms
        result = sock.connect_ex((ip, port))
        sock.close()
        return result == 0
    except Exception as e:
        return False # A port is considered to be open when the connection is established, else an exception is raise. Use try...catch to catch the exception.

def main(ip): # Should be able to pass an IP address as a command-line argument
    ports = [80, 443, 22, 25, 53] # Scan only ports 80,443, 22,25 and 53
    open_ports = []

    for port in ports:
        if scan_port(ip, port):
            open_ports.append(port)

    if open_ports:
        print(f"Open ports for {ip}: {', '.join(map(str, open_ports))}") #Print the open ports for the given IP address
    else:
        print(f"No open ports found for {ip}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python port_scanner.py <IP>")
        sys.exit(1)

    ip_address = sys.argv[1]
    main(ip_address) 

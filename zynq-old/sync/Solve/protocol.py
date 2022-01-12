from os import times
import socket
import struct
from io import BytesIO

CLOCK_FREQ = 25000000
PORT = 8091

class WaveInfo:
    pack = struct.Struct("Q Q Q")
    def __init__(self, count: int, timestamp: int, freq: int=0, start: int=0) -> None:
        self.count, self.timestamp = count, timestamp
        self.start = start
        self.freq = freq if freq <= 0 else CLOCK_FREQ // self.count

    def get_binary(self):
        return WaveInfo.pack.pack(self.count, self.timestamp, self.freq)
    
    @staticmethod
    def from_binary(data: bytes):
        dat = WaveInfo.pack.unpack(data)
        return WaveInfo(*dat)
    
    def __getstate__(self) -> dict:
        return self.__dict__
    
    def __str__(self) -> str:
        return str(self.__getstate__())

class Protocol:
    def __init__(self, wave_info: WaveInfo, wave_data=BytesIO) -> None:
        self.wave_info, self.wave_data = wave_info, wave_data
    
    def get_binary(self):
        header = self.wave_info.get_binary()
        self.wave_data.seek(self.wave_info.start)
        data = self.wave_data.read(self.wave_info.count)
        return header + data
    
    def send(self, addr: str, port: int=PORT):
        try:
            # print("Creating socket ...")
            client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        except socket.error as e:
            print("Error creating socket: " + str(e) + ". Exitting ...")
            # client_socket.close()
            raise e
        try:
            # print("Connecting to socket ... " + str(addr) + ":" + str(PORT))
            client_socket.connect((addr, PORT))
        except socket.error as e:
            print("Error connecting to socket: " + e + ". Exitting ...")
            client_socket.close()
            raise e
        
        print("Sending wave:", self.wave_info)
        data = self.get_binary()
        client_socket.sendall(data)
        client_socket.close()



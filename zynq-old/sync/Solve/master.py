from io import BytesIO
from re import I
import struct
from protocol import Protocol, WaveInfo, PORT
from wave import set_wave
from ptp2.ptp import run_master
import traceback
import socket

def start_server(port: int=PORT):
    try:
        print("Creating socket ...")
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error as e:
        print("Error creating socket: " + str(e) + ". Exitting ...")
        raise e
    try:
        print("Binding to socket ... " + ":" + str(port))
        server_socket.bind(("", port))
    except socket.error as e:
        print("Error binding to socket: " + str(e) + ". Exitting ...")
        server_socket.close()
        raise e
    
    print("Server Init ok. Start listening on %s..." % port)

    server_socket.listen(8)

    ok = True

    try:
        while ok:
            client_socket, addr = server_socket.accept()
            # 读取协议头
            header_data = client_socket.recv(WaveInfo.pack.size)
            try:
                wave_info = WaveInfo.from_binary(header_data)
            except struct.error as e:
                traceback.print_exc()
                ok = False
                break
            # 按照协议头读取数据部分
            print("Reading wave:", wave_info)
            wave_data_all = client_socket.recv(wave_info.count)
            wave_data = BytesIO(wave_data_all)
            # 协议写入BRAM
            pro = Protocol(wave_info=wave_info, wave_data=wave_data)
            set_wave(pro)
    except Exception as e:
        traceback.print_exc()
        raise e

def main(slaves: list):
    for slave in slaves:
        print('slave:', slave, "result:", run_master(slave, branch=100))
    start_server()

if __name__ == "__main__":
    main([
        "192.168.137.101"
    ])

import socket
import time
import struct
import traceback
import numpy as np

# import binascii
# import threading

debug = False

PORT = 8090
g_offset = 0
offsets_data = []
DIV = 100

class Times:
    def __init__(self, t1: int=0, t2: int=0, t3: int=0, t4: int=0):
        self.t1, self.t2, self.t3, self.t4 = t1, t2, t3, t4
    
    def get_tripple(self):
        return (self.t1, self.t2, self.t3, self.t4)
    
    @staticmethod
    def from_tripple(data):
        return Times(*data)

class Frame:
    PTP_FRAME_NULL = 0
    PTP_FRAME_SYNC = 1
    PTP_FRAME_FOLLOW_UP = 2
    PTP_FRAME_DELAY_REQ = 3
    PTP_FRAME_DELAY_RESP = 4
    PTP_FRAME_DELAY_ERR = 5
    pack = struct.Struct('H Q Q Q Q Q Q')
    cnt_id = 0

    def __init__(self, frame_type: int=PTP_FRAME_NULL, fid: int=-1, branch: int=1000, t1: int=0, t2: int=0, t3: int=0, t4: int=0):
        self.fid = fid
        if self.fid < 0:
            self.fid = Frame.cnt_id
            Frame.cnt_id += 1
        self.frame_type = frame_type
        self.branch = branch
        self.times = Times(t1, t2, t3, t4)
    
    def get_binary(self):
        return Frame.pack.pack(self.frame_type, self.fid, self.branch, *self.times.get_tripple())
    
    @staticmethod
    def from_binary(data: bytes):
        d = Frame.pack.unpack(data)
        return Frame(*d)
    
    def __getstate__(self):
        return {
            "fid": self.fid,
            "frame_type": self.frame_type,
            "branch": self.branch,
            "times": self.times.get_tripple()
        }
    
    def __str__(self):
        return str(self.__getstate__())

def get_freq():
    return 1000000
    
def timer():
    return int(time.time() * get_freq()) - int(g_offset)

def ptp_delay(times: Times) -> int:
    if times.t1 == 0 or times.t2 == 0 or times.t3 == 0 or times.t4 == 0:
        return 0
    return (times.t2 + times.t4 - times.t3 - times.t1) // 2;

def ptp_offset(times: Times) -> int:
    if times.t1 == 0 or times.t2 == 0 or times.t3 == 0 or times.t4 == 0:
        return 0
    return (times.t3 + times.t2 - times.t1 - times.t4) // 2;

def run_slave(loop: bool=False):
    global offsets_data
    try:
        print("Creating socket ...")
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    except socket.error as e:
        print("Error creating socket: " + str(e) + ". Exitting ...")
        # server_socket.close()
        raise e

    try:
        print("Binding to socket ... " + ":" + str(PORT))
        server_socket.bind(("", PORT))
    except socket.error as e:
        print("Error binding to socket: " + str(e) + ". Exitting ...")
        server_socket.close()
        raise e
    
    print("Slave Init ok. Start listening on %s..." % PORT)
    ok = True
    times = {}
    branch = 1000

    delays = 0
    offsets = 0
    cnt = 0

    addr = None
    frame = None

    try:
        while ok:
            data, addr = server_socket.recvfrom(4096)
            frame = Frame.from_binary(data)
            if debug:
                print(str(frame))
            if frame.frame_type == Frame.PTP_FRAME_SYNC:
                if frame.fid in times:
                    ok = False
                    print("Slave: err fid!")
                    break
                branch = frame.branch
                frame.times.t2 = timer()
                times[frame.fid] = frame.times
            elif frame.frame_type == Frame.PTP_FRAME_FOLLOW_UP:
                if frame.fid not in times:
                    ok = False
                    print("Slave: no fid!")
                    break
                times[frame.fid].t1 = frame.times.t1
                frame.frame_type = Frame.PTP_FRAME_DELAY_REQ
                times[frame.fid].t3 = timer()
                frame.times = times[frame.fid]
                # server_socket.sendall(frame.get_binary())
                server_socket.sendto(frame.get_binary(), addr)
            elif frame.frame_type == Frame.PTP_FRAME_DELAY_RESP:
                if frame.fid not in times:
                    ok = False
                    print("Slave: no fid!")
                    break
                times[frame.fid].t4 = frame.times.t4
                delay = ptp_delay(times[frame.fid])
                offset = ptp_offset(times[frame.fid])
                delays += delay
                offsets += offset
                cnt += 1
                if cnt % DIV == 0:
                    if debug:
                        print("Fin:", times[frame.fid].get_tripple())
                del times[frame.fid]
                if cnt == branch:
                    offset = offsets / (cnt - 1)
                    delay = delays / (cnt - 1)
                    global g_offset
                    g_offset = offset
                    print("======== Slave Done %s, g_offset:%s ========" % (timer(), g_offset))
                    offsets_data.append(offset)
                    print(np.array(offsets_data) / sum(offsets_data))
                    if loop:
                        cnt = 0
                        delays = 0
                        offsets = 0
                    else:
                        break
            else:
                ok = False
                print("Slave: Error pack!", data)
                break
    except struct.error as e:
        print("Data to unpack:", data)
        print(str(frame))
        traceback.print_exc()
        ok = False
        if addr is not None:
            server_socket.sendto(Frame(Frame.PTP_FRAME_DELAY_ERR).get_binary(), addr)
    except KeyboardInterrupt as e:
        print("Exiting...")
        raise e
    if not ok:
        return None
    else:
        return {
            "delay": delays / (cnt - 1),
            "offset": offsets / (cnt - 1)
        }
        

def run_master(addr: str, branch: int=1000, delay_time: float=0.05):
    try:
        print("Creating socket ...")
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    except socket.error as e:
        print("Error creating socket: " + str(e) + ". Exitting ...")
        # client_socket.close()
        raise e
    try:
        print("Connecting to socket ... " + str(addr) + ":" + str(PORT))
        client_socket.connect((addr, PORT))
    except socket.error as e:
        print("Error connecting to socket: " + e + ". Exitting ...")
        client_socket.close()
        raise e
    ok = True
    cnt = 0

    while ok:
        frame = Frame(Frame.PTP_FRAME_SYNC, branch=branch)
        client_socket.sendall(frame.get_binary())
        frame.frame_type = Frame.PTP_FRAME_FOLLOW_UP
        frame.times.t1 = timer()
        if debug:
            print("Sent", str(frame), frame.get_binary())
        client_socket.sendall(frame.get_binary())
        data, addr = client_socket.recvfrom(4096)
        frame = Frame.from_binary(data)
        if debug:
            print("Recv", str(frame), frame.get_binary())
        if frame.frame_type != Frame.PTP_FRAME_DELAY_REQ:
            ok = False
            print("Master: Error pack!")
            break
        frame.frame_type = Frame.PTP_FRAME_DELAY_RESP
        frame.times.t4 = timer()
        client_socket.sendall(frame.get_binary())
        cnt += 1
        if (cnt == branch):
            print('======== Master Done %s ========' % timer())
            break
        time.sleep(delay_time)
    
    client_socket.close()
    return ok



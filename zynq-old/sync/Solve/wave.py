from io import BytesIO
from pynq import Overlay, DefaultIP
from ptp2.ptp import timer
import time
from protocol import Protocol, WaveInfo

g_overlay = None

debug = False

class AdBramAll(DefaultIP):
    def __init__(self, description):
        super().__init__(description=description)

    bindto = ['chiro.work:ChiIP:ad2bram:0.3']
    
    def start(self):
        self.register_map.CTRL.AP_START = 1

    def is_done(self):
        return (self.register_map.CTRL.AP_DONE == 0)
    
    def is_idle(self):
        return (self.register_map.CTRL.AP_IDLE == 0)

    def is_ready(self):
        return (self.register_map.CTRL.AP_READY == 0)

    def set_values(self, depth=8192):
        self.register_map.depth = depth


def download(download: bool=True, re_download: bool=False):
    global g_overlay
    if g_overlay is not None and not re_download:
        return g_overlay
    overlay = Overlay("bits/pynq_ad_bram7/pynq_ad_bram7.bit", download=False)
    if download:
        overlay.download()
        print("Download Done!")
    g_overlay = overlay
    return overlay

def reverse_bits(n, bit=32):
    return int((((f"%{bit}s") % (bin(n)[2:])).replace(' ', '0'))[::-1], base=2)

def show_wave(data: BytesIO, values: dict, depth: int=128, max_val: int=2048, byte_size=2):
    data.seek(0)
    for i in range(depth):
        d = data.read(byte_size)
        if (len(d) != byte_size):
            break
        val = int().from_bytes(d, byteorder='big', signed=False)
        if i == values["start"]:
            print("/" + "=" * 18 + '\\')
        if i == values["end"]:
            print("\\" + "=" * 18 + '/')
        print("%-20s" % ("#" * int(20 * (val / max_val))), "%6s" % hex(val), ("%13s" % bin(val)[2:]).replace(' ', '0'))

def find_wave(data: BytesIO, depth: int=0xFF, threshold: int=-1, byte_size=2, rise: bool=True) -> dict:
    max_val, min_val = 0, 0xFFFFFFFF
    
    default_values = {
        "start": 0,
        "end": 0,
        "count": 0
    }
    values = {
        "start": 0,
        "end": 0,
        "count": 0
    }
    
    data.seek(0)
    dataset = []
    for _ in range(depth):
        d = data.read(byte_size)
        if (len(d) != byte_size):
            break
        val = int().from_bytes(d, byteorder='big', signed=False)
        dataset.append(val)
    
    max_val, min_val = max(dataset), min(dataset)
    if (threshold < 0):
        threshold = (max_val + min_val) / 2
    if debug:
        print("max:", max_val, "min:", min_val, "threshold:", threshold)
    
    start, middle, end = 0, 0, 0
    found = False
    for i in range(depth - 1):
        if rise and dataset[i] <= threshold and dataset[i + 1] > threshold:
            found = True
            start = i
            break
        elif dataset[i] >= threshold and dataset[i + 1] < threshold:
            found = True
            start = i
            break
    if not found:
        return default_values
    values.update({'start': start})
    if debug:
        print("Set start =", start)
    found = False
    for i in range(start - 1, depth - 1, 1):
        if rise and dataset[i] >= threshold and dataset[i + 1] < threshold:
            found = True
            middle = i
            break
        elif dataset[i] <= threshold and dataset[i + 1] > threshold:
            found = True
            middle = i
            break
    if not found:
        return default_values
    if debug:
        print("Set middle =", middle)
    found = False
    for i in range(middle - 1, depth - 1, 1):
        if rise and dataset[i] <= threshold and dataset[i + 1] > threshold:
            found = True
            end = i
            break
        elif dataset[i] >= threshold and dataset[i + 1] < threshold:
            found = True
            end = i
            break
    if not found:
        return default_values
    if debug:
        print("Set end =", end, ", count =", end - start)
    values.update({'end': end, 'count': end - start})
    if values['start'] < 0 or values['end'] <= 0 or values['count'] <= 0:
        return default_values
    return values


def get_wave(overlay=None) -> Protocol:
    if overlay is None:
        overlay = download(download=True)
        # print("Download done!")
    ad = overlay.ad2bram_0
    while not ad.is_ready():
        if debug:
            print("Waiting for ready...")
        time.sleep(1)
    ad.set_values(8192)
    ad.start()
    while not ad.is_done():
        if debug:
            print("Waiting for done...")
        time.sleep(1)
    if debug:
        print("All Done.")
    t = timer()
    out1 = overlay.bram_out1
    data = BytesIO()
    for i in range(16384):
        src = out1.read(i * 4)
        val = (src & 0xFF000000) >> 24
        data.write(int(val).to_bytes(length=1, byteorder='big', signed=False))
        if (i % 0xFF == 0):
            if debug:
                print('.', end='')
    if debug:
        print('Read & Write done.')
    values = find_wave(data, byte_size=1, depth=16384)
    if debug:
        print('values', values)
    if values["count"] == 0:
        values = find_wave(data, byte_size=1, depth=16384, rise=False)
        if debug:
            print('re-values', values)
    data.seek(0)
    if values["count"] == 0:
        return None
    return Protocol(wave_data=data, wave_info=WaveInfo(count=values["count"], timestamp=t, start=values["start"]))

def set_wave(pro: Protocol, overlay=None):
    if overlay is None:
        overlay = download(download=True)
        # print("Download done!")
    data = pro.wave_data
    data.seek(0)
    out2 = overlay.barm_out2
    i = 0
    while True:
        d = data.read(1)
        if not d:
            break
        d = int().from_bytes(d, signed=False, byteorder="big")
        out2.write(i * 4, (d << 24) & 0xFF000000)
        i += 1
    da = overlay.bram2da_start_0
    
    if debug:
        print(f"da.register_map.CTRL: {da.register_map.CTRL}")
        print(f"da.register_map.CTRL.AP_READY: {da.register_map.CTRL.AP_READY}")
    while da.register_map.CTRL.AP_READY != 0:
        if debug:
            print("Waiting da ready...")
        time.sleep(1)
    da.register_map.start_r = 0
    da.register_map.stop = (i - 1) * 4
    da.register_map.CTRL.AP_START = 1
    while da.register_map.CTRL.AP_DONE != 1:
        if debug:
            print("Waiting da done...")
        time.sleep(1)
    if debug:
        print("Da done.")

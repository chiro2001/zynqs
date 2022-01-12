from pynq import Overlay, DefaultIP


XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL = 0x00
XAD_FIFO_ALL_CONTROL_ADDR_GIE = 0x04
XAD_FIFO_ALL_CONTROL_ADDR_IER = 0x08
XAD_FIFO_ALL_CONTROL_ADDR_ISR = 0x0c
XAD_FIFO_ALL_CONTROL_ADDR_DIV_DATA = 0x10
XAD_FIFO_ALL_CONTROL_BITS_DIV_DATA = 32
XAD_FIFO_ALL_CONTROL_ADDR_THRESHOLD_DATA = 0x18
XAD_FIFO_ALL_CONTROL_BITS_THRESHOLD_DATA = 32
XAD_FIFO_ALL_CONTROL_ADDR_START_R_DATA = 0x20
XAD_FIFO_ALL_CONTROL_BITS_START_R_DATA = 32
XAD_FIFO_ALL_CONTROL_ADDR_START_R_CTRL = 0x24
XAD_FIFO_ALL_CONTROL_ADDR_END_R_DATA = 0x30
XAD_FIFO_ALL_CONTROL_BITS_END_R_DATA = 32
XAD_FIFO_ALL_CONTROL_ADDR_END_R_CTRL = 0x34
XAD_FIFO_ALL_CONTROL_ADDR_COUNT_DATA = 0x40
XAD_FIFO_ALL_CONTROL_BITS_COUNT_DATA = 32
XAD_FIFO_ALL_CONTROL_ADDR_COUNT_CTRL = 0x44
XAD_FIFO_ALL_CONTROL_ADDR_SUCCESS_DATA = 0x50
XAD_FIFO_ALL_CONTROL_BITS_SUCCESS_DATA = 32
XAD_FIFO_ALL_CONTROL_ADDR_SUCCESS_CTRL = 0x54


class AdAll(DefaultIP):
    def __init__(self, description):
        super().__init__(description=description)

    bindto = ['chiro.work:ChiIP:ad_fifo_all:0.32']

    def start(self):
        data = self.read(XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL) & 0x80
        self.write(XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL, data | 0x01)

    def is_done(self):
        data = self.read(XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL);
        return (data >> 1) & 0x1;
    
    def is_idle(self):
        data = self.read(XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL);
        return (data >> 2) & 0x1;

    def is_ready(self):
        data = self.read(XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL);
        # check ap_start to see if the pcore is ready for next input
        return ((data & 0x1) == 0);

    def set_values(self, div=0, bit=12):
        threshold = (1 << bit - 1) // 2
        self.write(XAD_FIFO_ALL_CONTROL_ADDR_DIV_DATA, div)
        self.write(XAD_FIFO_ALL_CONTROL_ADDR_THRESHOLD_DATA, threshold)
    
    def get_values(self):
        start = self.read(XAD_FIFO_ALL_CONTROL_ADDR_START_R_DATA)
        end = self.read(XAD_FIFO_ALL_CONTROL_ADDR_END_R_DATA)
        count = self.read(XAD_FIFO_ALL_CONTROL_ADDR_COUNT_DATA)
        success = self.read(XAD_FIFO_ALL_CONTROL_ADDR_SUCCESS_DATA)
        return {
            'start': start,
            'end': end,
            'count': count,
            'success': success
        }


overlay = Overlay("bits/ad_all/ad_all.bits")

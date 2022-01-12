import time
import traceback
from protocol import Protocol, WaveInfo
from ptp2.ptp import run_slave, timer
from wave import get_wave

SERVER_ADDR = "192.168.137.101"
# SERVER_ADDR = "127.0.0.1"

def main(master_ip: str = SERVER_ADDR):
    # 得到时间信息并且同步时间
    time_values = run_slave()
    print("Time values", time_values)
    while True:
        try:
            # 得到波形和对应时间戳
            pro: Protocol = get_wave()
            if pro is None:
                print("No Wave!")
                continue
            print("Send wave:", pro.wave_info)
            # 按照协议发送波形数据
            pro.send(master_ip)
        except Exception as e:
            print(e)
            traceback.print_exc()
            time.sleep(3)

if __name__ == "__main__":
    main()

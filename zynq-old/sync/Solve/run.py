from utils import get_mac

# MASTER_MAC = "9e:31:7f:b8:39:96".replace(":", "-")
MASTER_MAC = "d6:b0:6e:01:84:50".replace(":", "-")
MASTER_IP = "192.168.137.101"
SLAVE_IPS = [
    "192.168.137.102"
]

if get_mac() == MASTER_MAC:
    print("Starting Master...")
    import master
    master.main(SLAVE_IPS)
else:
    print("Starting Slave...")
    import slave
    slave.main(MASTER_IP)

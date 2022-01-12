import uuid

def get_mac() -> str:
    address = hex(uuid.getnode())[2:]
    return '-'.join(address[i:i+2] for i in range(0, len(address), 2))

if __name__ == '__main__':
    print(get_mac())

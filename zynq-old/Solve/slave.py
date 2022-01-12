from ptp2.ptp import run_slave

def main():
    while True:
        values = run_slave()
        if values is not None and 'delay' in values:
            delay = values["delay"]
            print(values)

if __name__ == "__main__":
    main()

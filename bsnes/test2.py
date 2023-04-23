import time
import bsnes

def update():
    time.sleep(1.5)
    d = bsnes.read_mem(0,0)
    print(f"test in pythniok! {d}")




import time

previous_time=0
current_time=0

previous_time=time.time()

print(previous_time)

time.sleep(5)

current_time=time.time()

print(current_time)

print(current_time-previous_time)

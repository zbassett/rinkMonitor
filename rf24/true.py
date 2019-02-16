import time

elapsed_time = 0

while True:
    print(f"I've been waiting {elapsed_time} seconds. still waiting...")
    time.sleep(5)
    elapsed_time = elapsed_time + 5
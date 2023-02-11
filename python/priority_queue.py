import heapq
import random

# heapq is the easiest way to develop priority queue
def big_root_heapq():
    l = []
    for i in range(10):
        heapq.heappush(l, -random.random())
    for i in range(len(l)):
        a = -heapq.heappop(l)
        print(a)

def small_root_heapq():
    l = []
    for i in range(10):
        heapq.heappush(l, random.random())
    for i in range(len(l)):
        a = heapq.heappop(l)
        print(a)


if __name__ == "__main__":
    print("from big root:")
    big_root_heapq()
    print("from small root:")
    small_root_heapq()
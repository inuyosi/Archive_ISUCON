from collections import deque

q = deque(["a","b","c"])
bad_count = deque([0,0,0])

if __name__ == "__main__":
    tmp = q.popleft()
    count = 0
    print (tmp + ":" + str(count))
    while (tmp != "c"):
        count += 1
        q.append(tmp)
        tmp = q.popleft()
        print (tmp + ":" + str(count))
    q.append(tmp)
    print (q)

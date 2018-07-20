from collections import deque

q = deque(["a","b","c"])
bad_count = deque([0,0,0])

if __name__ == "__main__":
    tmp = q.popleft()
    btmp = bad_count.popleft()
    count = 0
    print (tmp + ":" + str(count))
    if  (tmp != "c"):
        btmp += 1
        while (tmp != "c"):
            count += 1
            q.append(tmp)
            bad_count.append(btmp)
            tmp = q.popleft()
            btmp = bad_count.popleft()
            print (tmp + ":" + str(count))
        q.append(tmp)
        bad_count.append(btmp)
    print (q)
    print (bad_count)

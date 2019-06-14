# 挿入ソート
def insertion_sort(array):
    n = len(array)
    for i in range(1, n):
        tmp = array[i] # 挿入する値を退避
        if tmp < array[i-1]:
            # 挿入する位置までずらしていく
            j = i
            while True:
                array[j] = array[j-1]
                j -= 1
                if j == 0 or tmp >= array[j-1]:
                    break
            array[j] = tmp # 空いた位置に退避していた値を挿入

# デバッグ
if __name__ == "__main__":
    array = [1,2,3,4,5,3,2,1,4,3,4,5,0]
    print("before", array)
    insertion_sort(array)
    print("after ", array)
import numpy as np

Array = np.array((3,-4,5,2,-5,5,9,-9,-2,8))
NumOfData= Array.size

MinSoFar = 0
MinEndingHere = 0

for i in range(NumOfData):
    MinEndingHere = min(MinEndingHere + Array[i],0)
    MinSoFar = min(MinSoFar,MinEndingHere)

print(MinSoFar)

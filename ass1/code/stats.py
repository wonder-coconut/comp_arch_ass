import statistics

f = open("out")

accuracy = []

for x in f:
    if "Accuracy" in x:
        accuracy.append(float(x[10:18]))

print(f'Mean:\t{statistics.mean(accuracy)}')
print(f'StdDev:\t{statistics.stdev(accuracy)}')
import csv
import matplotlib.pyplot as plt

filename = "output.csv"

rows = []
#Get values from CSV
with open(filename, 'r') as csvFile:
    csvReader = csv.reader(csvFile)
    for row in csvReader:
        rows.append(row)

fig, ax = plt.subplots()

counter = 0
for queen in rows:
    counter = counter + 1
    #xVals = []
    #yVals = []
    x = int(queen[0])
    y = int(queen[1])
    #xVals.append(x)
    #yVals.append(y)
    plt.text(x+0.5, y+0.5, "Q", fontsize=12, color="red")

plt.grid(color="black", linestyle='-', linewidth=2)
plt.xticks(range(0,counter))
plt.yticks(range(0,counter))

plt.xlim(0, counter)
plt.ylim(0, counter)
plt.savefig("output.png", dpi=600)
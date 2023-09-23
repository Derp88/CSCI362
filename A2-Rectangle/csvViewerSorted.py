import csv
import matplotlib.pyplot as plt
import math

filename = "output.csv"

rows = []
rowsAngle = []
#Get values from CSV
with open(filename, 'r') as csvFile:
    csvReader = csv.reader(csvFile)
    for row in csvReader:
        rows.append(row)

with open("outputAngleSort.csv", 'r') as csvFile:
    csvReader = csv.reader(csvFile)
    for rowAgnle in csvReader:
        rowsAngle.append(rowAgnle)
    
fig, ax = plt.subplots()

counter = 0
colors = ["blue", "orange", "red", "green"]
for circle in rows:
    
    x = int(circle[0])
    y = int(circle[1])
    radius = int(circle[2])
    x1 = float(circle[3])
    x2 = float(circle[4])
    x3 = float(circle[5])
    x4 = float(circle[6])
    y1 = float(circle[7])
    y2 = float(circle[8])
    y3 = float(circle[9])
    y4 = float(circle[10])
    Xs = [x1, x2, x4, x3, x1]
    Ys = [y1, y2, y4, y3, y1]
    plt.plot(Xs, Ys)

for angleInterval in rowsAngle:
    counter = counter + 1
    selectColor = counter % len(colors)
    minSlope = math.tan(float(angleInterval[0]) * math.pi / 180)
    maxSlope = math.tan(float(angleInterval[1]) * math.pi / 180)

    plt.axline((0,0), slope = minSlope, color = colors[selectColor], alpha = 0.2)
    plt.axline((0,0), slope = maxSlope, color = colors[selectColor], alpha = 0.2)

plt.plot(0,0, marker="x", color="red")
plt.xlim(-275, 275)
plt.ylim(-275, 275)
plt.show()
plt.savefig("outputSorted.png", dpi=600)
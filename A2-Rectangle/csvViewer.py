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
#plt.figure(dpi=300)

counter = 0
colors = ["blue", "orange", "red", "green"]
for circle in rows:
    counter = counter + 1
    selectColor = counter % len(colors)
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
    #ax.scatter([x1,x2,x3,x4],[y1,y2,y3,y4], color="purple")
    #circlePlot = plt.Circle((x, y), radius, color=colors[selectColor])
    
    #ax.add_patch(circlePlot)
    Xs = [x1, x2, x4, x3, x1]
    Ys = [y1, y2, y4, y3, y1]
    plt.plot(Xs, Ys)

plt.plot(0,0, marker="x", color="red")
plt.xlim(-275, 275)
plt.ylim(-275, 275)
plt.show()
plt.savefig("output.png", dpi=600)
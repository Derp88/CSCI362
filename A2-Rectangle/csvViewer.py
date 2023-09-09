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
    circlePlot = plt.Circle((x, y), radius, color=colors[selectColor])
    
    ax.add_patch(circlePlot)

plt.xlim(-275, 275)
plt.ylim(-275, 275)
plt.show()
plt.savefig("output.png", dpi=600)
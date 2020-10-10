#Plotting, (x and y Eulerian Coordinates)

#Importing Our Plotting Library
import matplotlib.pyplot as plt

#Defining Our Two Arrays That Will Function As Our Eulerian Coordinates
xEulerian = []
yEulerian = []

#We Open Our Produced File And Read Through Its Lines
file = open("FlappingPlateOptimization.txt", "r")
for line in file.readlines():

    Coordinates = line.split()

    xEulerian.append(Coordinates[0])
    yEulerian.append(Coordinates[1])

#We Now Plot Our Calculated Vector Of Eulerian Coordinates And Save The Figure
plt.plot(xEulerian, yEulerian, "r--"); 
plt.axis('equal')
plt.title("2D Deformed Foil")
#plt.legend()
plt.savefig("Defomation_Optimization.png")
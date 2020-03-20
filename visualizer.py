import matplotlib.pyplot as plt 
import numpy as np 

x = [10, 10, 20, 20, 20, 20, 30, 30, 30, 30, 30, 40, 40, 40, 40, 50, 50, 50, 10, 10]

y =  [10, 20, 15, 25, 35, 45, 50, 40, 30, 20, 10, 15, 25, 35, 45, 40, 30, 20, 40, 50]

plt.style.use("ggplot")

plt.plot(x, y)
plt.show()
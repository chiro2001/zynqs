import matplotlib.pyplot as plt
import numpy as np

data_in, data_out = [], []

with open("in.dat", "r") as f:
    lines = f.readlines()
    for line in lines:
        data_in.append(float(line))

with open("out.dat", "r") as f:
    lines = f.readlines()
    for line in lines:
        # if 'e' in line:
        #     line = line.split('e')[-1]
        # print(line)
        if np.isnan(float(line)):
            data_out.append(float(0))
        else:
            data_out.append(float(line))

data_in, data_out = np.array(data_in), np.array(data_out)
data_out = np.clip(data_out, -1.0e+100, 1.0e+100)
# data_out =np.clip(data_out, -10, 10)

x = np.array([i for i in range(max([data_in.shape[0], data_out.shape[0]]))])

print("in", data_in.shape, "out", data_out.shape)
print(data_out)

plt.plot(x, data_in, ls="-", lw=2, label="input")
plt.plot(x, data_out, ls="-", lw=2, label="output")
plt.legend()
plt.show()

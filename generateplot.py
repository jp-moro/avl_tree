import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick

datanor = np.loadtxt('NormalMedia.txt')
#dataseq = np.loadtxt('normalMedia.txt')
#datagpu = np.loadtxt('opencl-nvidiaMedia.txt')

datagpu = np.loadtxt('ParaleloGPUMedia.txt')
dataseq = np.loadtxt('SequencialMedia.txt')

sorted_datanor = np.sort(datanor)
sorted_dataseq = np.sort(dataseq)
sorted_datagpu = np.sort(datagpu)

yvalsnor=np.arange(len(sorted_datanor))/float(len(sorted_datanor)-1)
yvalsseq=np.arange(len(sorted_dataseq))/float(len(sorted_dataseq)-1)
yvalsgpu=np.arange(len(sorted_datagpu))/float(len(sorted_datagpu)-1)

plt.plot(sorted_dataseq,yvalsseq,sorted_datanor,yvalsnor,sorted_datagpu,yvalsgpu)

plt.legend(['Sequential', 'Normal(CPU)', 'OpenCL(GPU)'], loc='best')
plt.title("Lookup Time")
plt.ylim((0, 1))
plt.ylabel("CDF")
plt.grid(True)

plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))

plt.show()

shepard_interp
==============

numpy interface to shepard algorithm from http://people.sc.fsu.edu/~jburkardt/c_src/sparse_interp_nd/sparse_interp_nd.html
compile with cmake in an extra directory
example usage:
import shepard_interp
import numpy as np
import matplotlib.pyplot as pl
xr=np.random.rand(2,700)*2-1
x=np.linspace(-1,1,10)
y=np.linspace(-1,1,10)
xx,yy=np.meshgrid(x,y)
xg=np.asarray([xx.flatten(),yy.flatten()])
f=np.exp(-xr[0,:]**2)+np.sin(xr[1,:])
ff=shepard_interp.shepard_interp_nd(xr,f,xg,2.)
ff.shape=10,-1
pl.imshow(ff)
pl.show()


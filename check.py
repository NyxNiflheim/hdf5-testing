import h5py, numpy as np
with h5py.File("data/cube.h5","r") as f:
    p = f["pressure"][...]
print("min/max/mean:", p.min(), p.max(), p.mean())

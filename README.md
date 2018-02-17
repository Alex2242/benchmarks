# Scientific benchmarks

## Build

Requirements :
```
	Cuda
	gcc-6
	cmake
```


To build the project : ` cmake . && make ` on linux.



## Architectures

Check [CUDA GPUs](https://developer.nvidia.com/cuda-gpus) for the best architecture to use with your hardware.


`compute_30,sm_30` is used by default for wider compatibility, remplace it in CMakeLists.txt with yours.

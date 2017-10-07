# Scientific benchmarks

## Build

To build the project, you need : 
	CUDA gcc(4.7-5) cmake 

Run : ` cmake . && make ` on linux.
If you get the error : `unsupported GNU version! gcc versions later than 5 are not supported!` then run `cmake .` twice before make.

## Architectures 

Check [CUDA GPUs](https://developer.nvidia.com/cuda-gpus) for the best architecture to use with your hardware. 
`compute_20,sm_20` is used by default for wider compatibility, remplace it in CMakeLists.txt with yours.



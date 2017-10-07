cmake_minimum_required(VERSION 3.0)

project(scientific_benchmark)

# Modify path for gcc 5 here
set(CUDA_HOST_COMPILER /usr/bin/gcc-5)
find_package(CUDA QUIET REQUIRED)

include_directories(${CUDA_INCLUDE_DIRS})
#link_directories(/opt/cuda/lib64)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set(
    CUDA_NVCC_FLAGS
    ${CUDA_NVCC_FLAGS};
    -O3 -gencode arch=compute_20,code=sm_20
)


SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC") 


cuda_add_executable(cuda_gemm_fp32 src/cgemm.cu src/gene_bruit_rayleigh_scalaire.c)
target_link_libraries (cuda_gemm_fp32 ${CUDA_CUBLAS_LIBRARIES} )
install(TARGETS cuda_gemm_fp32 DESTINATION bin)

cuda_add_executable(cuda_gemm_fp64 src/zgemm.cu src/gene_bruit_rayleigh_scalaire.c)
target_link_libraries (cuda_gemm_fp64 ${CUDA_CUBLAS_LIBRARIES} )
install(TARGETS cuda_gemm_fp64 DESTINATION bin)



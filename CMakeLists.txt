cmake_minimum_required(VERSION 3.0)

project(scientific_benchmark)

# Modify path for gcc 5 or 6 here
find_package(CUDA)

if (CUDA_FOUND)
	set(CUDA_HOST_COMPILER /usr/bin/gcc-6)

	include_directories(${CUDA_INCLUDE_DIRS})
	#link_directories(/opt/cuda/lib64)

	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
	set(
	    CUDA_NVCC_FLAGS
	    ${CUDA_NVCC_FLAGS};
	    #-O3 -gencode arch=compute_20,code=sm_20 # became usupported
	    -O3 -gencode arch=compute_30,code=sm_30
	)


	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")


	cuda_add_executable(cuda_gemm_fp32 src/cgemm.cu src/generateRayleighScalarNoise.c)
	target_link_libraries (cuda_gemm_fp32 ${CUDA_CUBLAS_LIBRARIES} )
	install(TARGETS cuda_gemm_fp32 DESTINATION bin)

	cuda_add_executable(cuda_gemm_fp64 src/zgemm.cu src/generateRayleighScalarNoise.c)
	target_link_libraries (cuda_gemm_fp64 ${CUDA_CUBLAS_LIBRARIES} )
	install(TARGETS cuda_gemm_fp64 DESTINATION bin)

endif()

find_package(SDL2)
find_package(OpenGL)
find_package(Boost)

if (SDL2_FOUND)
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fpermissive")
	add_executable(nbody src/nbody/main.cpp src/nbody/nbody.cpp src/nbody/display.cpp src/nbody/glcamera.cpp )
	target_link_libraries(nbody SDL2 OpenGL GLU)
endif()

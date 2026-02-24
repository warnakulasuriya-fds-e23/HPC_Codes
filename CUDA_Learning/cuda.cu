#include <cuda_runtime_api.h>
#include <stdio.h>


__global__ void gpu_hello_world(){
	printf("Hello world, from thread %d\n", threadIdx.x	);
}

int main(){

	gpu_hello_world<<<2,5>>>();

	cudaDeviceSynchronize();
	return 0;
}

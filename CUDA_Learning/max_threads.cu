#include <iostream>
#include <cuda_runtime.h>

int main() {
    int deviceCount;
    cudaGetDeviceCount(&deviceCount);

    if (deviceCount == 0) {
        std::cout << "No CUDA-capable devices found." << std::endl;
        return 1;
    }

    for (int i = 0; i < deviceCount; i++) {
        cudaDeviceProp prop;
        cudaGetDeviceProperties(&prop, i);

        std::cout << "--- Device " << i << ": " << prop.name << " ---" << std::endl;
        std::cout << "  Compute Capability:          " << prop.major << "." << prop.minor << std::endl;
        std::cout << "  Multiprocessor (SM) Count:   " << prop.multiProcessorCount << std::endl;
        std::cout << "  Max Threads Per Block:       " << prop.maxThreadsPerBlock << std::endl;
        std::cout << "  Max Threads Per SM:          " << prop.maxThreadsPerMultiProcessor << std::endl;
        
        // Calculate theoretical maximum concurrent threads
        long totalThreads = (long)prop.multiProcessorCount * prop.maxThreadsPerMultiProcessor;
        std::cout << "  Total Concurrent Threads:    " << totalThreads << std::endl;

        std::cout << "  Max Grid Size:               (" 
                  << prop.maxGridSize[0] << ", " 
                  << prop.maxGridSize[1] << ", " 
                  << prop.maxGridSize[2] << ")" << std::endl;
    }

    return 0;
}
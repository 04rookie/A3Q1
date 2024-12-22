#include <cuda_runtime.h>
#include <math_constants.h>
__global__ void gkernel(int n, float h, float* x, float* y) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n) {
        const double d = 1.0 / sqrtf(2 * (CUDART_PI));
        double sum = 0.0;
        double k = 0.0;
        for(int j = 0; j < n; j++){
            k = (x[i] - x[j])/h;
            sum += d * __expf(-(k * k) / 2);
        }
        y[i] = (1.0/(n*h)) * sum;
    }
    return;
}

__host__ void run_gkernel(int n, float h, float* x, float* y){
    int block_size = 1024;
    int num_blocks = (n + block_size -1)/block_size;
    gkernel<<<num_blocks, block_size>>>(n, h, x, y);
}
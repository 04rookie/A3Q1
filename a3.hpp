/*  Atharva Vikas
 *  Jadhav
 *  ajadhav9
 */

#ifndef A3_HPP
#define A3_HPP

#include <cuda_runtime.h>
void run_gkernel(int n, float h, float *x, float *y);

void kde_seq(int n, float h, const std::vector<float> &x, std::vector<float> &y)
{
    const double PI = 3.14159265358979323846;
    const double d = 1.0 / sqrt(2 * (PI));

    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        double k = 0.0;
        for (int j = 0; j < n; j++)
        {
            k = (x[i] - x[j]) / h;
            sum += d * exp(-(k * k) / 2);
        }
        y[i] = (1.0 / (n * h)) * sum;
    }
    return;
}

void gaussian_kde(int n, float h, const std::vector<float> &x, std::vector<float> &y)
{
    // kde_seq(n, h, x, y);
    // return;

    int size = n * sizeof(float);

    float *d_x;
    float *d_y;

    cudaMalloc(&d_x, size);
    cudaMalloc(&d_y, size);

    cudaMemcpy(d_x, x.data(), size, cudaMemcpyHostToDevice);
    cudaDeviceSynchronize();
    run_gkernel(n, h, d_x, d_y);
    cudaDeviceSynchronize();
    cudaMemcpy(y.data(), d_y, size, cudaMemcpyDeviceToHost);

    cudaFree(d_x);
    cudaFree(d_y);
    return;
} // gaussian_kde

#endif // A3_HPP

#include <chrono>
#include <iostream>
#include <random>

const int N = 1000;
const int TRIALS = 10;

// Allocate 2D array A and 1D arrays x and y
double A[N][N], B[N][N], C[N][N];

// Compute y = Ax
void run()
{
    // Implement here
	#pragma omp parallel for
	for(int i = 0;i<N;i++){
		for(int j = 0;j<N;j++) {
			C[i][j]=0;
			for(int k = 0; k<N;k++){
				C[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
}

int main()
{
    // Initialize A and x with random values
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_real_distribution<> dist(-1.0, 1.0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = dist(engine);
			B[i][j] = dist(engine);
        }
    }

    // Run benchmark for TRIALS times
	double average = 0;
    for (int i = 0; i < TRIALS; i++) {
        // Start timer
        const std::chrono::steady_clock::time_point start =
            std::chrono::steady_clock::now();

        // Run the actual computation
        run();

        // Stop timer
        const std::chrono::steady_clock::time_point end =
            std::chrono::steady_clock::now();

        // Calculate and print runtime
        std::chrono::duration<double, std::milli> runtime = end - start;
        std::cout << "runtime: " << runtime.count() << " [ms]" << std::endl;
		average += runtime.count();
    }
	std::cout << "average runtime: " << average/TRIALS << " [ms]" << std::endl;
}
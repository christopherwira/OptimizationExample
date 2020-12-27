#include <chrono>
#include <iostream>
#include <random>

const int N = 10000;
const int TRIALS = 10;

// Allocate 2D array A and 1D arrays x and y
double A[N][N], x[N], y[N];

// Compute y = Ax
void run()
{
	#pragma omp parallel for
    // Implement here
	for(int i = 0;i<N;i++){
		y[i]=0;
		for(int j = 0;j<N;j++) {
			y[i]+=A[i][j]*x[j];
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
        x[i] = dist(engine);

        for (int j = 0; j < N; j++) {
            A[i][j] = dist(engine);
        }
    }

    // Run benchmark for TRIALS times
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
    }
}
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <numeric>
#include <random>
#include <functional>

const int DATA_COMPUTATION_SIZE = 1e8;


// Function to perform a heavy computation
void heavyComputationRef(std::vector<int>& data, int id) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < DATA_COMPUTATION_SIZE; ++i) {
        //data.push_back(dis(gen));
        data[i] = dis(gen);
    }

    // Sum up the numbers to simulate a heavy computation
    std::accumulate(data.begin(), data.end(), 0);
    
    std::cout << id << " FINISHED.\n";
}

void heavyComputation(int id) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(1, 100);

    std::vector<int> data(DATA_COMPUTATION_SIZE);

    for (int i = 0; i < DATA_COMPUTATION_SIZE; ++i) {
        //data.push_back(dis(gen));
        data[i] = dis(gen);
    }

    // Sum up the numbers to simulate a heavy computation
    std::accumulate(data.begin(), data.end(), 0);

    std::cout << id << " FINISHED.\n";
}


void runSingleThreaded(int numRuns) {
    std::vector<int> data(DATA_COMPUTATION_SIZE);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numRuns; ++i) {
        heavyComputation(i);
        //heavyComputationRef(data, i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Single-threaded duration: " << duration.count() << " seconds" << std::endl;
}

void runMultiThreaded(int numRuns) {
    std::vector<std::vector<int>> dataContainer(numRuns);
    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numRuns; i++)
    {
        //std::vector<int> data(DATA_COMPUTATION_SIZE);
        //dataContainer[i] = data;
        //threads.emplace_back(heavyComputation, std::ref(dataContainer[i]), i);
        

        threads.emplace_back(heavyComputation, i);

        
    }
    
    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Multi-threaded duration: " << duration.count() << " seconds" << std::endl;
}

int main() {

    std::cout << "Running multi-threaded computation..." << std::endl;
    runMultiThreaded(12);

    std::cout << "Running single-threaded computation..." << std::endl;
    runSingleThreaded(12);



    return 0;
}

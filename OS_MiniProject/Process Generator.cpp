#include <iostream>
#include <random>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
using namespace std;


int main(int argc, char* argv[]) {

	if (argc != 3)
		throw invalid_argument("Invalid arguments, should be InputFileName OutputFileName");

	string inputFile = argv[1];
	string outputFile = argv[2];

	//redirect buffer to files
	freopen(inputFile.c_str(), "r", stdin);
	freopen(outputFile.c_str(), "w", stdout);

	int processCount;

	double arrivalTimeMean, arrivalTimeSigma;
	double burstTimeMean, burstTimeSigma;
	double priorityMean;

	cin >> processCount;

	if (processCount < 0)
		throw out_of_range("Negative number of processes");

	cin >> arrivalTimeMean >> arrivalTimeSigma;

	if (arrivalTimeMean < 0)
		throw out_of_range("Negative number arrival time mean");

	if (arrivalTimeSigma < 0)
		throw out_of_range("Negative number arrival time sigma");

	cin >> burstTimeMean >> burstTimeSigma;

	if (burstTimeMean < 0)
		throw out_of_range("Negative number burst time mean");

	if (burstTimeSigma < 0)
		throw out_of_range("Negative number burst time sigma");

	cin >> priorityMean;

	if (priorityMean < 0)
		throw out_of_range("Negative number priority mean");

	//current time to generate random numbers at each run
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	//engines that handles random
	default_random_engine arrivalEngine (seed);
	default_random_engine burstEngine (seed);
	default_random_engine priorityEngine (seed);

	//Process parameters generators
	normal_distribution<double> arrivalTimeGenerator(arrivalTimeMean, arrivalTimeSigma);
	normal_distribution<double> burstTimeGenerator(burstTimeMean, burstTimeSigma);
	poisson_distribution<int>	priorityGenerator(priorityMean);

	cout << processCount << endl;

	//parameters for each process
	double arrivalTime, burstTime;
	int priority;

	for (int i = 1; i <= processCount; ++i)
	{
		arrivalTime = arrivalTimeGenerator(arrivalEngine);
		burstTime = burstTimeGenerator(burstEngine);
		priority = priorityGenerator(priorityEngine);


		cout << i << " " << arrivalTime << " " << burstTime << " " << priority << endl;
	}
	return 0;
}
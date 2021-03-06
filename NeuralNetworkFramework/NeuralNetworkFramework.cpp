/* NeuralNetworkFramework.cpp
2018-02-27 Andy Eck
This is a demo file for the NeuralNetwork class

Trains an NN with 1 hidden layer to predict outputs of a NAND gate.
Though this example is trivial, it is intended to study how the weights at different points of the neural network evolve as training data comes in,
and study the effects of changing parameters of the NN such as nodes per layer, Regularization cost, and Step Size for learning.

Uses test/train data in csv files generated to simulate a NAND gate, which should accompany this code as "nandData.csv" and "nandTestData.csv"

Outputs the success rate of the NN in predicting the output of the NAND gate.

*/

#include "NeuralNetwork.h"
#include "../CSVReader/CSVReader.h"
#include <fstream>
#include <iostream>


int main()
{
	NeuralNetwork myNet;
	std::vector<int> nodesPerLayer({ 2, 5, 4, 1 });
	myNet.Initialize(nodesPerLayer);
	myNet.SetHiddenLayerActivationFunctions(NNUtilityFunctions::sigmoidFunc, NNUtilityFunctions::sigmoidFunc_deriv);
	myNet.SetOutputLayerActivationFunctions(NNUtilityFunctions::binaryClassifierActivFunc, NNUtilityFunctions::binaryClassifierActivFunc_deriv);
	myNet.LEARNING_STEP_SIZE = 0.001;
	myNet.REGULARIZATION_WEIGHT = 0.001;

	std::cout << "Training network..." << std::endl;
	myNet.TrainNetwork("../TrainingData/nandData.csv",2,1);
	std::cout << "Finished training network\n\n" << std::endl;

	std::cout << "Testing network..." << std::endl;
	std::vector<double> successFraction = myNet.TestNetwork("../TrainingData/nandTestData.csv", 2, 1);
	std::cout << "Finished testing network\n\n" << std::endl;

	std::cout << "Fraction of successful predictions: " << successFraction[0] << std::endl;
	std::cout << "Press ENTER to exit...\n" << std::endl;
	getchar();
	
    return 0;
}


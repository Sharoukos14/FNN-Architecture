# FNN-Architecture
This project was part of the Computational Intelligence undergraduate course in the CSE Department at UoI. Focused on the architecture of an MLP for classification of 2D spatial points. It was developed using C.

Execution:

Initially, the data must be generated using the generator to make the training and test data.

Generator Execution:
gcc classificationProblemExamplesGenerator.c -o GEN 

exexute Command : ./GEN

Afterwards, the user selects the model to execute PT2 with 2 Hidden layers or PT3 with 3 Hidden layers
and execute accordingly.

PT2:
gcc PT2.c -o PT2 -lm

exexute Command : ./PT2

PT3:
gcc PT3.c -o PT3 -lm

exexute Command : ./PT3


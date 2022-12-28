# Anthony Redamonti
# Advanced Computer Architecture
# Qiskit Logical Expression Test
# 11-4-2021

import time
from qiskit import BasicAer
from qiskit.aqua.algorithms.amplitude_amplifiers import Grover
from qiskit.aqua.components.oracles import LogicalExpressionOracle
from qiskit.tools.visualization import plot_histogram

# a logical expression to be evaluated by Grover's Algorithm
logicalExpression = '(((a & b) | (c & d)) & ~(e & f))'

# initialize Grover's Algorithm with the logic expression
algorithm = Grover(LogicalExpressionOracle(logicalExpression))

# initialize the back end with the quantum simulator provided by IBM
backend = BasicAer.get_backend('qasm_simulator')

# Start the timer
StartTime1 = time.time()

# Execute the algorithm
result = algorithm.run(backend, shots = 1024)

# Stop the timer
EndTime1 = time.time()

# Calculate and display the total time taken by the quantum simulator
TotalTime = (EndTime1 - StartTime1)
print("The total time for the 6-bit calculation: {0}".format("{:.{}f}".format(TotalTime, 8)))

# Plot the results.
plot_histogram(result['measurement'], title = "Possible Combinations", bar_labels = True, figsize = (15,5))
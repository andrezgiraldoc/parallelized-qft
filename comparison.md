# Sequential QFT vs parallel QFT

Below is a comparison of the results obtained after executing the sequential code to carry out the QFT vs its parallel counterpart

## Characteristics of the computer for tests

These are the characteristics of the computer where the tests were performed:

* MacBook Pro (13-inch, 2017, Two Thunderbolt 3 ports)
* Processor: 2.3 GHz Intel Core i5
* Memory: 8 GB 2133 MHz LPDDR3
* CPU's (sysctl -n hw.ncpu): 4 

### Sequential QFT

These are the results obtained from the execution of the sequential code for QFT for different numbers of qubits:

| Number of Qubits | Execution time (s) |
| --- | --- |
| 1 | 3.2e-05 |
| 2 | 5.3e-05 |
| 3 | 5.4e-05 |
| 4 | 0.000298 |
| 5 | 0.000775 |
| 6 | 0.000998 |
| 7 | 0.004786 |
| 8 | 0.01422 |
| 9 | 0.057937 |
| 10 | 0.21662 |
| 11 | 0.861326 |
| 12 | 3.4312 |
| 13 | 14.3116 |
| 14 | 75.9824 |
| 15 | 347.936 |

### Parallelized QFT

These are the results obtained from the execution of the parallelized code for QFT for different numbers of qubits:

| Number of Qubits | Execution time (s) |
| --- | --- |
| 1 | 0.001537 |
| 2 | 0.001685 |
| 3 | 0.002396 |
| 4 | 0.003589 |
| 5 | 0.009274 |
| 6 | 0.011181 |
| 7 | 0.013659 |
| 8 | 0.036652 |
| 9 | 0.109008 |
| 10 | 0.399536 |
| 11 | 1.56906 |
| 12 | 5.48309 |
| 13 | 18.8896 |
| 14 | 91.6223 |
| 15 | 390.303 |

### Conclusion

The changes that were made did not improve the performance of the sequential code.






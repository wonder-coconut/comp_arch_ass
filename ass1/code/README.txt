To run the code, execute the following shell instructions

1. $ make branch_predictor
2. $ ./branch_predictor <command line arguments>

The arguments are formatted as such:
<predictor algorithm> <trace filepath> <n bit limit> <h bit limit>

The n and h bit limits depend on which predictor is chosen:
- n is mandatory for dynamic_lt and dynamic_gshare
- h is mandatory for dynamic_gshare
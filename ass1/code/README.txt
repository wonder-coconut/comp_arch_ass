To run the code, execute the following shell instructions

1. $ make branch_predictor
2. $ ./branch_predictor <command line arguments>

The arguments are formatted as such:
<predictor algorithm> <trace filepath> <n bit limit> <h bit limit>

The n and h bit limits depend on which predictor is chosen:
- n is mandatory for dynamic_lt and dynamic_gshare
- h is mandatory for dynamic_gshare

Alternatively, you can also use the exec.sh bash script to run all traces for a defined predictor.
It uses identical command line arguments.
Note: the relative path between the scripts and the traces are hardcoded and must be in an identically placed folder to run.

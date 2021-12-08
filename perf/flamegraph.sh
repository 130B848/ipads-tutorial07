
#step 1 build perf
# cd /path/to/kernel/tools
# make perf

#step 2 download flamegraph src code
# wget https://github.com/brendangregg/FlameGraph/archive/master.zip
# unzip master.zip
# export PATH=$PATH:/path/to/FlameGraph

#step 3 generate perf sample file
sudo perf record -F 99 --call-graph lbr -g -o in-fb.data ./a.out
sudo perf script -i in-fb.data > in-fb.perf

#step 4 generate flamegraph
./FlameGraph/stackcollapse-perf.pl in-fb.perf > in-fb.folded
./FlameGraph/flamegraph.pl in-fb.folded >in-fb-cpu.svg

#step 5 use browser to open flamegraph.svg


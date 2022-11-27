# Sыsbench.
apt-get update > /dev/null
curl -s https://packagecloud.io/install/repositories/akopytov/sysbench/script.deb.sh | sudo bash
apt -y install sysbench


echo Running 1st benchmark
sysbench --threads=10 --time=60 cpu --cpu-max-prime=64000 run

echo Running 2nd benchmark
sysbench --num-threads=64 --test=threads --thread-yields=100 --thread-locks=2 run

echo Running 3rd benchmark
sysbench --threads=10 --time=60 memory --memory-oper=write run

echo Running 4th benchmark
sysbench --test=memory --memory-block-size=1M --memory-total-size=10G run

echo Running 5th benchmark
sysbench --test=fileio --file-total-size=32G prepare > /dev/null
sysbench --test=fileio --file-total-size=32G --file-test-mode=rndrw --time=120 --max-time=300 --max-requests=0 run
sysbench --test=fileio --file-total-size=32G cleanup > /dev/null

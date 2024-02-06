# spdlog-vs-zlog

[![ci](https://github.com/iamazeem/spdlog-vs-zlog/actions/workflows/ci.yml/badge.svg)](https://github.com/iamazeem/spdlog-vs-zlog/actions/workflows/ci.yml)

spdlog vs zlog benchmarks

- [spdlog 1.12.0](https://github.com/gabime/spdlog/releases/tag/v1.12.0)
- [zlog 1.2.16](https://github.com/HardySimpson/zlog/releases/tag/1.2.16)
  - Both [`zlog_*`](https://hardysimpson.github.io/zlog/UsersGuide-EN.html#htoc28)
    and [`dzlog_*`](https://hardysimpson.github.io/zlog/UsersGuide-EN.html#htoc33)
    APIs are benchmarked.
  - See [zlog.conf](zlog.conf) and [dzlog.conf](dzlog.conf) for their
    respective configurations.

Tested on Linux and macOS runners via CI. See the most recent run under
[Actions](https://github.com/iamazeem/spdlog-vs-zlog/actions) tab for the latest
results.

## Scenario

Comparing `spdlog` and `zlog` in multithreaded context with file rotation.

### Default Parameters

- Threads: 10
- Iterations: 1,000,000 (100,000 per thread)
- Rotation: 10 MB (5 files)
- Optimization Level: `O3`

## Setup

Clone:

```shell
git clone --recursive https://github.com/iamazeem/spdlog-vs-zlog.git
cd spdlog-vs-zlog
```

Build `zlog` :

```shell
cd zlog
make PREFIX=$PWD/build
make PREFIX=$PWD/build install
cd ..
```

## Build

```shell
cmake -S . -B build
cmake --build build
```

or,

```shell
mkdir build
cd build
cmake ..
make
```

## Run

```shell
$ cd build
$ ./spdlog-vs-zlog
[2024-02-06 15:05:17.122] [info] threads: 10, iterations: 100,000 per thread
[2024-02-06 15:05:18.910] [info] spdlog, elapsed time:   1.79 secs, logs/sec:     55,925/sec
[2024-02-06 15:06:46.941] [info]   zlog, elapsed time:  88.03 secs, logs/sec:      1,135/sec
[2024-02-06 15:08:13.512] [info]  dzlog, elapsed time:  86.57 secs, logs/sec:      1,155/sec
```

The rotated log files are generated under `/tmp` directory:

```shell
ls /tmp/{spdlog,zlog,dzlog}*
```

The [CI workflow](.github/workflows/ci.yml) removes these log files after each
iteration:

```shell
for i in {1..5}; do
    echo "Run $i"
    ./spdlog-vs-zlog
    echo
    rm /tmp/{spdlog,zlog,dzlog}*
done
```

## License

[MIT](LICENSE)

# spdlog-vs-zlog

[![ci](https://github.com/iamazeem/spdlog-vs-zlog/actions/workflows/ci.yml/badge.svg)](https://github.com/iamazeem/spdlog-vs-zlog/actions/workflows/ci.yml)

spdlog vs zlog benchmarks

- [spdlog 1.12.0](https://github.com/gabime/spdlog/releases/tag/v1.12.0)
- [zlog 1.2.16](https://github.com/HardySimpson/zlog/releases/tag/1.2.16)

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
git clone --recursive git@github.com:iamazeem/spdlog-vs-zlog.git
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

## Run

```shell
$ cd build
$ ./spdlog-vs-zlog 
[2023-08-15 09:51:57.568] [info] spdlog, elapsed:   0.12 secs, logs/sec:    817,639/sec
[2023-08-15 09:51:57.779] [info]   zlog, elapsed:   0.21 secs, logs/sec:    473,812/sec
```

## License

[MIT](LICENSE)

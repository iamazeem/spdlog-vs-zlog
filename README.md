# spdlog-vs-zlog

[![ci](https://github.com/iamazeem/spdlog-vs-zlog/actions/workflows/ci.yml/badge.svg)](https://github.com/iamazeem/spdlog-vs-zlog/actions/workflows/ci.yml)

spdlog vs zlog benchmarks

- [spdlog 1.12.0](https://github.com/gabime/spdlog/releases/tag/v1.12.0)
- [zlog 1.2.16](https://github.com/HardySimpson/zlog/releases/tag/1.2.16)
- [WinZlog](https://github.com/lopsd07/WinZlog/commit/03a95719e4782d83bc6787da3247989034079d1f)

## Default Parameters

- Threads: 10
- Iterations: 1,000,000 (100,000 per thread)
- Rotation: 30 MB (5 files)
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
mkdir build
cd build
cmake ..
make
```

## Run

```shell
$ ./spdlog-vs-zlog 
[2023-08-14 23:07:23.127] [info] spdlog, elapsed: 0.08 secs, logs/sec:  1,224,619/sec
[2023-08-14 23:07:23.281] [info]   zlog, elapsed: 0.15 secs, logs/sec:    648,189/sec
```

## License

[MIT](LICENSE)

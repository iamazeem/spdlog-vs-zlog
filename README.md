# spdlog-vs-zlog

spdlog vs zlog benchmarks

- [spdlog 1.12.0](https://github.com/gabime/spdlog/releases/tag/v1.12.0)
- [zlog 1.2.16](https://github.com/HardySimpson/zlog/releases/tag/1.2.16)

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
mkdir build && cd build
cmake ..
make
```

## Run

```shell
$ ./spdlog-vs-zlog
[2023-08-14 21:43:36.878] [info] spdlog, elapsed: 0.12 secs, logs/sec: 830,431/sec
[2023-08-14 21:43:37.094] [info]   zlog, elapsed: 0.22 secs, logs/sec: 463,186/sec
```

## License

[MIT](LICENSE)

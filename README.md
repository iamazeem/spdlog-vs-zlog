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
[2023-08-14 21:36:56.360] [info] logger: spdlog, iterations: 100,000, threads: 10, elapsed: 0.12 secs, logs/sec: 839,550/sec
[2023-08-14 21:36:56.574] [info] logger:   zlog, iterations: 100,000, threads: 10, elapsed: 0.21 secs, logs/sec: 468,513/sec
```

## License

[MIT](LICENSE)

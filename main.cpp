#include <string>
#include <thread>
#include <vector>
#include <cstdlib>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

#include "zlog.h"

static constexpr std::size_t max_file_size = 10 * 1024 * 1024;
static constexpr std::size_t max_rotating_files = 5;
static constexpr std::size_t max_threads = 100;

void bench_spdlog(const std::size_t iterations, const std::size_t thread_count) noexcept
{
    auto logger = spdlog::rotating_logger_mt("rotating_mt", "/tmp/spdlog", max_file_size, max_rotating_files);
    logger->set_pattern("%Y-%m-%d %T.%e %l [%P:%t] %v");

    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    const auto start = std::chrono::high_resolution_clock::now();

    for (std::size_t t = 0; t < thread_count; t++)
    {
        threads.emplace_back(
            [&]()
            {
                for (std::size_t i = 1; i <= iterations; i++)
                {
                    logger->info("message number # {}", i);
                }
            });
    }

    for (auto &t : threads)
    {
        t.join();
    }

    const auto end = std::chrono::high_resolution_clock::now() - start;
    const auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end).count();

    spdlog::info(spdlog::fmt_lib::format(std::locale("en_US.UTF-8"),
                                         "spdlog, elapsed time: {:>6.2f} secs, logs/sec: {:>10L}/sec",
                                         elapsed, int(iterations / elapsed)));

    spdlog::drop(logger->name());
}

void bench_zlog(const std::size_t iterations, const std::size_t thread_count) noexcept
{
    if (zlog_init("../zlog.conf"))
    {
        spdlog::error("zlog_init() failed");
        return;
    }

    const auto zc = zlog_get_category("default_category");
    if (!zc)
    {
        spdlog::error("zlog_get_category() failed");
        return;
    }

    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    const auto start = std::chrono::high_resolution_clock::now();

    for (std::size_t t = 0; t < thread_count; t++)
    {
        threads.emplace_back(
            [&]()
            {
                for (std::size_t i = 1; i <= iterations; i++)
                {
                    zlog_info(zc, "message number # %zu", i);
                }
            });
    }

    for (auto &t : threads)
    {
        t.join();
    }

    const auto end = std::chrono::high_resolution_clock::now() - start;
    const auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end).count();

    spdlog::info(spdlog::fmt_lib::format(std::locale("en_US.UTF-8"),
                                         "  zlog, elapsed time: {:>6.2f} secs, logs/sec: {:>10L}/sec",
                                         elapsed, int(iterations / elapsed)));

    zlog_fini();
}

void bench_dzlog(const std::size_t iterations, const std::size_t thread_count) noexcept
{
    if (dzlog_init("../dzlog.conf", "default_category"))
    {
        spdlog::error("dzlog_init() failed");
        return;
    }

    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    const auto start = std::chrono::high_resolution_clock::now();

    for (std::size_t t = 0; t < thread_count; t++)
    {
        threads.emplace_back(
            [&]()
            {
                for (std::size_t i = 1; i <= iterations; i++)
                {
                    dzlog_info("message number # %zu", i);
                }
            });
    }

    for (auto &t : threads)
    {
        t.join();
    }

    const auto end = std::chrono::high_resolution_clock::now() - start;
    const auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end).count();

    spdlog::info(spdlog::fmt_lib::format(std::locale("en_US.UTF-8"),
                                         " dzlog, elapsed time: {:>6.2f} secs, logs/sec: {:>10L}/sec",
                                         elapsed, int(iterations / elapsed)));

    zlog_fini();
}

int main(int argc, char **argv)
{
    spdlog::set_automatic_registration(false);
    spdlog::default_logger()->set_pattern("%+");

    std::size_t iterations = 100'000;
    std::size_t thread_count = 10;

    try
    {
        if (argc > 1)
        {
            iterations = std::stoi(argv[1]);
        }
        if (argc > 2)
        {
            thread_count = std::stoul(argv[2]);
        }
        if (thread_count > max_threads)
        {
            throw std::runtime_error(spdlog::fmt_lib::format("number of threads exceeds maximum [{}]", max_threads));
        }

        spdlog::info(spdlog::fmt_lib::format(std::locale("en_US.UTF-8"),
                                             "threads: {:L}, iterations: {:L} per thread", thread_count, iterations));

        bench_spdlog(iterations, thread_count);
        bench_zlog(iterations, thread_count);
        bench_dzlog(iterations, thread_count);
    }
    catch (const std::exception &e)
    {
        spdlog::error(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

#include <string>
#include <thread>
#include <memory>
#include <cstdlib>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

static constexpr std::size_t file_size = 30 * 1024 * 1024;
static constexpr std::size_t rotating_files = 5;
static constexpr std::size_t max_threads = 1000;

void bench_mt(const std::shared_ptr<spdlog::logger> logger, const std::size_t iterations, const std::size_t thread_count) noexcept
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;

    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    const auto start = high_resolution_clock::now();
    for (size_t t = 0; t < thread_count; ++t)
    {
        threads.emplace_back(
            [&]()
            {
                for (std::size_t i = 1; i <= (iterations / thread_count); i++)
                {
                    logger->info("Hello logger: msg number {}", i);
                }
            });
    }

    for (auto &t : threads)
    {
        t.join();
    };

    const auto delta = high_resolution_clock::now() - start;
    const auto delta_d = duration_cast<duration<double>>(delta).count();

    spdlog::info(spdlog::fmt_lib::format(std::locale("en_US.UTF-8"),
                                         "logger: {}, iterations: {:>L}, threads: {}, elapsed: {:0.2f} secs, logs/sec: {:>L}/sec",
                                         logger->name(), iterations, thread_count, delta_d, int(iterations / delta_d)));
    spdlog::drop(logger->name());
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
            throw std::runtime_error(spdlog::fmt_lib::format("Number of threads exceeds maximum({})", max_threads));
        }

        auto rotating_mt = spdlog::rotating_logger_mt("rotating_mt", "logs/rotating_mt.log", file_size, rotating_files);
        rotating_mt->set_pattern("%Y-%m-%d %T.%o %l [%P:%t] %v");
        bench_mt(std::move(rotating_mt), iterations, thread_count);
    }
    catch (const std::exception &e)
    {
        spdlog::error(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

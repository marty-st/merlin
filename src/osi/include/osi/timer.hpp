#ifndef OSI_TIMER_INCLUDE
#define OSI_TIMER_INCLUDE

#include <util/math.hpp>

#include <chrono>

namespace osi
{

/**
 * Allows the underlying app to access measured time during execution.
 */
class Timer
{
    // Number of loop iterations since the osi::run() function was called.
    std::uint64_t passed_iterations = 0ULL;
    // Double precision time passed since the first iteration, (1.0 equals 1s)
    double passed_seconds = 0.0;
    // Elapsed time between the previous and the current frame, (1.0f equals 1s)
    float time_delta = 0.0f;
    // When `false`, the update method call is skipped and only the render method is called in the run loop
    bool pause = false;

    // std::chrono::steady_clock never decreases, epoch might start for example during system boot.

    // Time, which was the `current_time` for the previous iteration, 
    // has to be fetched by std::chrono::steady_clock::now() before first use
    std::chrono::time_point<std::chrono::steady_clock> last_iteration_time;
    // Current time, has to be fetched by std::chrono::steady_clock::now() before first use
    std::chrono::time_point<std::chrono::steady_clock> current_time;
    // Time interval represented by double arithmetics with a period of 1 second (1.0 equals 1s)
    std::chrono::duration<double> duration = {}; // For milisecond period: duration<double,std::ratio<1,1000>>

public:
    /**
     * @return Number of loop iterations since the osi::run() function was called.
     */
    std::uint64_t passedIterations() const { return passed_iterations; }

    /**
     * @return Seconds passed since the first iteration
     */
    double passedSeconds() const { return passed_seconds; }

    /**
     * @return Elapsed time between the previous and the current frame, (1.0f equals 1s)
     */
    float dt() const { return time_delta; }

    /**
     * @return `true` if the update loop is paused, `false` otherwise
     */
    bool paused() const { return pause; }

    /**
     * When set to `true` the update method of the application will be skipped in the upcoming iterations. 
     * @param _pause Determines whether the update loop should be on pause
     */
    void setPause(bool const _pause) { pause = _pause; }

    /**
     * Initializes itaration related variables, specifically last_iteration_time before its first use.
     */
    void initialize()
    {
        last_iteration_time = std::chrono::steady_clock::now();
    }

    /**
     * Updates `current_time` and `time_delta` of the timer.
     */
    void updateBeforeFrame()
    {
        current_time = std::chrono::steady_clock::now();
        duration = current_time - last_iteration_time;

        last_iteration_time = current_time;

        // Could also pick std::min between duration count and some set max delta time
        time_delta = static_cast<float>(duration.count());
    }

    /**
     * Updates `passed_seconds`, increases `passed_iterations`, and resets `time_delta` of the timer.
     */
    void updateAfterFrame()
    {
        passed_seconds += static_cast<double>(time_delta);
        ++passed_iterations;
        time_delta = 0.0f; 
    }
};

} // namespace osi

#endif

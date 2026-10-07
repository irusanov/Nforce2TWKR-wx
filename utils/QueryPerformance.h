#ifndef HEADER_9E41476BC91C077B
#define HEADER_9E41476BC91C077B

#pragma once

class QueryPerformance {
private:
    // Use the full 64-bit counters, the low 32 bits of the TSC wrap every
    // ~2 seconds at 2 GHz which made some measurements fail
    unsigned long long ReadTsc() {
        DWORD eax = 0, edx = 0;
        Rdtsc(&eax, &edx);
        return (static_cast<unsigned long long>(edx) << 32) | eax;
    }

    long long GetQPCTime() {
        LARGE_INTEGER qpcTime;
        QueryPerformanceCounter(&qpcTime);
        return qpcTime.QuadPart;
    }

    long long GetQPCRate() {
        LARGE_INTEGER qpcRate;
        QueryPerformanceFrequency(&qpcRate);
        return qpcRate.QuadPart;
    }

public:
    QueryPerformance(void) {
    }

    ~QueryPerformance(void) {
    }

    // Returns CPU frequency in MHz, 0 on failure
    double MeasureCPUFrequency() {
        double qpcRate = static_cast<double>(GetQPCRate());
        double frequency = 0;
        int retries = 6;

        if (qpcRate <= 0) {
            return 0;
        }

        while(frequency <= 0 && retries > 0) {
            unsigned long long rdtscStart = ReadTsc();
            long long qpcStart = GetQPCTime();

            Sleep(50);

            unsigned long long rdtscEnd = ReadTsc();
            long long qpcElapsed = GetQPCTime() - qpcStart;

            if (qpcElapsed > 0 && rdtscEnd > rdtscStart) {
                double seconds = qpcElapsed / qpcRate;
                frequency = static_cast<double>(rdtscEnd - rdtscStart) / seconds / 1000000.0;
            }

            retries--;
        }

        return frequency > 0 ? frequency : 0;
    }
};
#endif // header guard


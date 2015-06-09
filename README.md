# kf5-cpufrequtility

CPU Frequence Utility.
For Linux, tested on Intel CPU.

Used paths:

/sys/devices/system/cpu/cpu*/cpufreq/scaling_available_frequencies
        contents available freq* (2001 2000 1600 1200 800)
/sys/devices/system/cpu/cpu*/cpufreq/scaling_available_governors
        contents available governor regimes
/sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
        for change regime
/sys/devices/system/cpu/cpu*/cpufreq/scaling_cur_freq
        current freq (for ex.: 800)
/sys/devices/system/cpu/cpu*/cpufreq/scaling_max_freq
        current max freq
/sys/devices/system/cpu/cpu*/cpufreq/scaling_min_freq
        current min freq
/sys/devices/system/cpu/cpu*/online
        enable\disable(1\0) proc, not for cpu0
/sys/devices/system/cpu/possible
        check possible proc (for ex.: 0-1)
/sys/devices/system/cpu/present
        check present proc (for ex.: 0-1)

# CPUFreqUtility

KDE CPU Frequence Utility.\n
For Linux, tested on Intel CPU.

Used paths:

# contents available freq*
(for ex.: 2001 2000 1600 1200 800)\n
/sys/devices/system/cpu/cpu*/cpufreq/scaling_available_frequencies
        
# contents available governor regimes
/sys/devices/system/cpu/cpu*/cpufreq/scaling_available_governors
        
# for change regime
/sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
        
# current freq
(for ex.: 800)\n
/sys/devices/system/cpu/cpu*/cpufreq/scaling_cur_freq
        
# current max freq
/sys/devices/system/cpu/cpu*/cpufreq/scaling_max_freq
        
# current min freq
/sys/devices/system/cpu/cpu*/cpufreq/scaling_min_freq
        
# enable\disable(1\0) proc,
not for cpu0\n
/sys/devices/system/cpu/cpu*/online
        
# check possible proc
(for ex.: 0-1)\n
/sys/devices/system/cpu/possible
        
# check present proc
(for ex.: 0-1)\n
/sys/devices/system/cpu/present

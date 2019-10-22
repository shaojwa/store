
## 用命令

    // 0是ssd
    // 1是hdd

    lsblk |  awk '{print $1}' | grep ^s | xargs -i cat /sys/block/{}/queue/rotational
    or
    lsblk -d -o name,rota

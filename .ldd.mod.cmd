savedcmd_/home/ubuntu/kernel-code/ldd.mod := printf '%s\n'   ldd.o | awk '!x[$$0]++ { print("/home/ubuntu/kernel-code/"$$0) }' > /home/ubuntu/kernel-code/ldd.mod

make
makerom -f cia -o RipEXAnim3DS.cia -elf Anim3DS.elf -rsf resources/Anim3DS.rsf -icon resources/icon.icn -banner resources/banner.bnr -exefslogo -target t
echo "Built CIA"
pause
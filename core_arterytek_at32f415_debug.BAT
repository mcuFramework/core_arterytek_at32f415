SET PATH=C:\Keil_v5\ARM\ARMCLANG\Bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\RedHat\java-1.8.0-openjdk-1.8.0.252-2\bin;C:\Program Files\RedHat\java-1.8.0-openjdk-1.8.0.252-2\jre\bin;C:\Program Files (x86)\Microchip\MPLAB C32 Suite\bin;C:\Users\Danny\.dnx\bin;C:\Program Files\Microsoft DNX\Dnvm\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\130\Tools\Binn\;C:\Program Files\PuTTY\;C:\MinGW\bin;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\110\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\DTS\Binn\;C;C:\Program Files\TortoiseGit\bin;C:\Program Files\Git\cmd;C:\Users\Danny\AppData\Local\Microsoft\WindowsApps;C:\Users\Danny\AppData\Local\GitHubDesktop\bin;C:\Users\Danny\AppData\Local\Programs\Microsoft VS Code\bin;C:\Program Files\JetBrains\CLion 2020.2.4\bin;
SET CPU_TYPE=AT32F415R8T7
SET CPU_VENDOR=ArteryTek
SET UV2_TARGET=core_arterytek_at32f415_debug
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\core.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\coreinterrupt.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\coreiomux.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\coregeneralpin.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\coregeneralport.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\coreedgetrigger.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\coreserialperiph.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\coreserialport.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\coreserialportpacket.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\coretimer.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\core_arterytek_interrupt.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\core_arterytek_interrupt_priority.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmAsm" --Via ".\.keil\objects\core_arterytek_startup._ia"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\mcuf_lib.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\rtx_lib.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\entry.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\serialporttest.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\.keil\objects\main.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmLink" --Via ".\.keil\Objects\core_arterytek_at32f415_debug.lnp"
"C:\Keil_v5\ARM\ARMCLANG\Bin\fromelf.exe" ".\.keil\Objects\core_arterytek_at32f415_debug.axf" --i32combined --output ".\.keil\Objects\core_arterytek_at32f415_debug.hex"

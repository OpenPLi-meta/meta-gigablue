SRCDATE = "20211026.r0"

require gb-v3ddriver.inc

SRC_URI[md5sum] = "c9242414250ef556de3350105c4e2bf3"
SRC_URI[sha256sum] = "776a24373c371ff5288ab198c102459e9a4b017b9ec4a4e356b8ce6ad3b489f2"
COMPATIBLE_MACHINE = "gbquad4k|gbue4k"

INSANE_SKIP = "32bit-time"

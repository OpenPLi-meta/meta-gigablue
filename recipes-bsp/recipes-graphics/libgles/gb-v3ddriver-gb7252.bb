SRCDATE = "20211026.r0"

require gb-v3ddriver.inc
require gb-v3ddriver-gb7252.inc


PREFERRED_PROVIDER_virtual/egl = "gb-v3ddriver-gb7252"
PREFERRED_PROVIDER_virtual/libgles2 = "gb-v3ddriver-gb7252"

COMPATIBLE_MACHINE = "gbquad4k|gbue4k"

INSANE_SKIP = "32bit-time"

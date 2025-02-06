KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"

MACHINE_FEATURES += "3dtv alsa hdmicec switchoff"

MACHINE_DRIVER = "\
${@bb.utils.contains('MACHINE', 'gb800se', 'gb7325' , '', d)}\
${@bb.utils.contains('MACHINE', 'gb800seplus', 'gb7358' , '', d)}\
${@bb.utils.contains('MACHINE', 'gb800solo', 'gb7325' , '', d)}\
${@bb.utils.contains('MACHINE', 'gb800ue', 'gb7325' , '', d)}\
${@bb.utils.contains('MACHINE', 'gb800ueplus', 'gb7358' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbipbox', 'gb7358' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbquad', 'gb7356' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbquadplus', 'gb7356' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbultrase', 'gb7362' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbultraue', 'gb7362' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbx1', 'gb7362' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbx3', 'gb7362' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbx2', 'gb73625' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbultraueh', 'gb73625' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbx3h', 'gb73625' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbquad4k', 'gb7252' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbquad4kpro', 'gb7252pro' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbue4k', 'gb7252' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbtrio4k', 'gbtrio4k' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbtrio4kpro', 'gbtrio4kpro' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbip4k', 'gbip4k' , '', d)}\
${@bb.utils.contains('MACHINE', 'gbx34k', 'gb72604' , '', d)}\
"

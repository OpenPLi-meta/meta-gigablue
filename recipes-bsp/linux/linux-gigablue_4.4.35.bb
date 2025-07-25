DESCRIPTION = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

COMPATIBLE_MACHINE = "^(gbtrio4k)$|^(gbtrio4kpro)$"

KERNEL_RELEASE = "4.4.35"
SRCDATE = "20220929"

inherit kernel machine_kernel_pr

MACHINE_KERNEL_PR_append = ".8"

SRC_URI[md5sum] = "5724ab24328d5767209cea0ea5a123b4"
SRC_URI[sha256sum] = "f1880fbf67022983b6ed231c54aaa00bc1f18b2db4a275e44ad0b7d4997436cf"


# By default, kernel.bbclass modifies package names to allow multiple kernels
# to be installed in parallel. We revert this change and rprovide the versioned
# package names instead, to allow only one kernel to be installed.
PKG_${KERNEL_PACKAGE_NAME}-base = "kernel-base"
PKG_${KERNEL_PACKAGE_NAME}-image = "kernel-image"
RPROVIDES_${KERNEL_PACKAGE_NAME}-base = "kernel-${KERNEL_VERSION}"
RPROVIDES_${KERNEL_PACKAGE_NAME}-image = "kernel-image-${KERNEL_VERSION}"

SRC_URI += "http://downloads.openpli.org/archive/gigablue/gigablue-linux-${PV}-${SRCDATE}.tar.gz \
    file://defconfig \
    file://0001-remote.patch \
    file://HauppaugeWinTV-dualHD.patch \
    file://dib7000-linux_4.4.179.patch \
    file://dvb-usb-linux_4.4.179.patch \
    file://initramfs-subdirboot.cpio.gz;unpack=0 \
    file://findkerneldevice.py \
    file://0002-log2-give-up-on-gcc-constant-optimizations.patch \
    file://0003-dont-mark-register-as-const.patch \
    file://wifi-linux_4.4.183.patch \
    file://fix-dvbcore.patch \
    file://fix-multiple-defs-yyloc.patch \
    file://fix_highspeed_sdio.patch \
    file://fix-build-with-binutils-2.41.patch \
    file://extend_modules_space.patch \
    file://cfg80211_Add_option_to_report_the_bss_entry_in_connect_result.patch \
"

SRC_URI_append_gbtrio4k = " \
    file://emmc_ks81aa80_05s000_reboot.patch \
"

S = "${WORKDIR}/linux-${PV}"
B = "${WORKDIR}/build"

export OS = "Linux"
KERNEL_OBJECT_SUFFIX = "ko"
KERNEL_IMAGEDEST = "tmp"
KERNEL_IMAGETYPE = "uImage"
KERNEL_OUTPUT = "arch/${ARCH}/boot/${KERNEL_IMAGETYPE}"

KERNEL_EXTRA_ARGS = "EXTRA_CFLAGS=-Wno-attribute-alias"

FILES_${KERNEL_PACKAGE_NAME}-image = "/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} /${KERNEL_IMAGEDEST}/findkerneldevice.py"

kernel_do_configure_prepend() {
	install -d ${B}/usr
	install -m 0644 ${WORKDIR}/initramfs-subdirboot.cpio.gz ${B}/
}
kernel_do_install_append() {
	install -d ${D}/${KERNEL_IMAGEDEST}
	install -m 0755 ${KERNEL_OUTPUT} ${D}/${KERNEL_IMAGEDEST}
	install -m 0755 ${WORKDIR}/findkerneldevice.py ${D}/${KERNEL_IMAGEDEST}
}

pkg_postinst_kernel-image () {
    if [ "x$D" == "x" ]; then
        if [ -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} ] ; then
            python /${KERNEL_IMAGEDEST}/findkerneldevice.py
            dd if=/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} of=/dev/kernel
        fi
    fi
    true
}

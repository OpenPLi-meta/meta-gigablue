DSCRIPTION = "GigaBlue bluetooth plugin"
PRIORITY = "required"
LICENSE = "CLOSED"
# require conf/license/license-close.inc

DEPENDS = "python3-native"
RDEPENDS:${PN} = "libcurl libsqlite3 libssl libcrypto libudev libusb-compat libudev1-compat libcrypto-compat"
RDEPENDS:${PN} += "gb-bluetooth-util"

PROVIDES += "enigma2-plugin-systemplugins-bluetoothsetup"
RPROVIDES:${PN} += "enigma2-plugin-systemplugins-bluetoothsetup"

RREPLACES:${PN} = "enigma2-plugin-systemplugins-bluetoothsetup"

PR="${SRCDATE}.${SRCDATE_PR}"

SRC_URI = " \
     http://downloads.openpli.org/archive/gigablue/enigma2-plugin-bluetoothsetup-gb7252-${PR}.tar.gz \
     file://port-to-python3.patch \
"

S = "${WORKDIR}/plugin"

BLUETOOTH_PLUGIN_PATH = "/usr/lib/enigma2/python/Plugins/SystemPlugins/BluetoothSetup"

do_install() {

	install -d  ${D}${BLUETOOTH_PLUGIN_PATH}
	cp -r ${S}/* ${D}${BLUETOOTH_PLUGIN_PATH}

}

do_package_qa() {
}

FILES:${PN} = "${BLUETOOTH_PLUGIN_PATH}"

do_populate_sysroot[noexec] = "1"

PACKAGE_ARCH = "${MACHINE_ARCH}"

INSANE_SKIP:${PN} = "already-stripped"


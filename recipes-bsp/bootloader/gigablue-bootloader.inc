SUMMARY = "Gigablue BOLT 2nd bootloader update"
SECTION = "base"
PRIORITY = "required"
MAINTAINER = "Gigablue"
LICENSE = "proprietary"
PACKAGE_ARCH = "${MACHINE}"

require conf/license/license-gplv2.inc

SRC_URI = "http://downloads.openpli.org/archive/gigablue/initrd_${MACHINE}_${SRCDATE}.zip"

S = "${WORKDIR}"

PV = "${BOLT_VERSION}-${BOLT_DATE}"
PR = "r1"

FILES:${PN} = "/tmp"

do_install() {
    install -d ${D}/tmp
    install -m 0644 bolt_${SRCDATE_BOLT}.bin  ${D}/tmp/${MACHINE}_bolt_${SRCDATE_BOLT}.bin
}

pkg_postinst:${PN}() {
#!/bin/bash

BOLT_FILE="/tmp/${MACHINE}_bolt_${SRCDATE_BOLT}.bin"

CURRENT_BOLT_DATE=$(cat /proc/device-tree/bolt/date | awk '{print $1}')

# Check device model
DEVICE_MODEL=$(cat /proc/stb/info/gbmodel)

echo "Starting bootloader update for ${MACHINE_BRAND} ${MACHINE_NAME}..."
echo "Detected model: $DEVICE_MODEL"

if [[ "$DEVICE_MODEL" != "${MACHINE}" ]]; then
    echo "Error: This update is only for model '${MACHINE}'. Detected model '$DEVICE_MODEL' is not supported."
    exit 1
fi
echo "Model verification passed: $DEVICE_MODEL"

# Check current bootloader version date
echo "Current bootloader date: $CURRENT_BOLT_DATE"
echo "Target bootloader date: ${BOLT_DATE}"

if [[ "$CURRENT_BOLT_DATE" == "${BOLT_DATE}" ]]; then
    echo "The bootloader is already up-to-date. No update required."
    exit 0
else
    echo "A newer bootloader version is available. Proceeding with the update..."
fi

# Verify MD5 hash
echo "Verifying MD5 hash of the bootloader file..."
MD5_ACTUAL=$(md5sum "$BOLT_FILE" | awk '{print $1}')

if [[ "$MD5_ACTUAL" != "${BOLT_MD5SUM}" ]]; then
    echo "MD5 hash mismatch. Bolt image corrupt. Aborting."
    exit 1
fi
echo "MD5 hash verified successfully."

# Perform the update
echo "Starting the flash process with dd to $FLASH_DEVICE..."
dd if="${BOLT_FILE}" of="${BOLT_DEVICE}" bs=4M conv=fsync

if [[ $? -ne 0 ]]; then
    echo "Error flashing the bootloader. Aborting."
    exit 1
fi
echo "Bootloader updated successfully."

# Final message
echo "Bootloader update completed."
echo "New bootloader version: ${BOLT_VERSION}, date: ${BOLT_DATE}"
exit 0
}

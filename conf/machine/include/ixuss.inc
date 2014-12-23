# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

MTD_ROOTFS = "mtd2"
MTD_KERNEL = "mtd1"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.bin"

DVBPROVIDER = "kernel"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = " \
    ixuss-dvb-modules-${MACHINE} \
    "

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = "\
    kernel-module-cdfs \
    "

MACHINE_EXTRA_RRECOMMENDS = " \
    ixuss-shutdown \
    gst-plugin-dvbmediasink \
    ntfs-3g \
    "

KERNEL_MODULE_AUTOLOAD += "xfs"

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dtsdownmix --with-eac3"

TARGET_ARCH = "mipsel"
DEFAULTTUNE = "mips32el"

PREFERRED_PROVIDER_virtual/kernel = "linux-ixuss"
PREFERRED_VERSION_linux-ixuss = "3.3.0"

KERNEL_IMAGETYPE = "vmlinux"
KERNEL_OUTPUT = "${KERNEL_IMAGETYPE}"
KERNEL_CONSOLE = "ttyS0,115200n8"

IMAGE_FSTYPES ?= "ubi"

UBI_VOLNAME = "rootfs"
MKUBIFS_ARGS = "-m 2048 -e 126976 -c 4096 -F"
UBINIZE_ARGS = "-m 2048 -p 128KiB"

IMAGE_CMD_ubi_prepend = " \
    rm -rf ${IMAGE_ROOTFS}/boot/*; \
    rm -rf ${IMAGE_ROOTFS}/tmp/*; \
    "

# do we need bootlogo? add after mkdir...
# cp ${DEPLOY_DIR_IMAGE}/cfe-bootlogo.bmp ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/cfe-bootlogo.bmp;

IMAGEDIR ?= "medialink/${MACHINE}"

IMAGE_CMD_ubi_append = " \
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    cp ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.rootfs.ubi ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.bin; \
    gzip -9c ${DEPLOY_DIR_IMAGE}/vmlinux-${MACHINE}.bin > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/kernel.bin; \
    echo ${DISTRO_NAME}-${DISTRO_VERSION}-${DATE} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
    echo "rename this file to 'force' to force an update without confirmation" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/noforce; \
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_usb.zip ${IMAGEDIR}/*; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.ubifs; \
    rm -rf ${IMAGEDIR}; \
    "

MACHINE_FEATURES += "3dtv alsa hdmicec switchoff textlcd wlan kernelwifi externalwifi"

MACHINE_KERNEL_PR = "r3"

require conf/machine/include/tune-mips32.inc

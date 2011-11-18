# This is a generic product that isn't specialized for a specific device.
# It includes the base Android platform. If you need Google-specific features,
# you should derive from generic_with_google.mk

$(call inherit-product, $(SRC_TARGET_DIR)/product/generic.mk)

PRODUCT_PACKAGES += \
	LedTest \
	LedClient

PRODUCT_COPY_FILES += \
    device/mokoid/mldk/com.mokoid.server.xml:system/etc/permissions/com.mokoid.server.xml

#PRODUCT_COPY_FILES += \
#    device/mokoid/mldk/cdata.ko:root/lib/modules/cdata.ko

# If we get a real board, put these in.
#PRODUCT_COPY_FILES += \
#    device/mokoid/dma6410xp/init.rc:root/init.rc \
#    device/mokoid/dma6410xp/init.dma6410xp.rc:root/init.dma6410xp.rc

# Overrides (see build.prop for results)
PRODUCT_NAME := mldk
PRODUCT_DEVICE := mldk

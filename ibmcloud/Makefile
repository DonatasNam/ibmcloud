
include $(TOPDIR)/rules.mk

PKG_NAME:=ibmcloud
PKG_VERSION:=1.0.0
PKG_RELEASE:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/ibmcloud
	DEPENDS:=+libubus +libubox +libibm-c +libblobmsg-json +libargp
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=Example program that interacts with ubus process
endef

define Package/ibmcloud/install
	$(INSTALL_DIR) $(1)/usr/bin $(1)/etc/config $(1)/etc/config $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ibmcloud $(1)/usr/bin
	$(INSTALL_BIN) ./files/ibmcloud.init $(1)/etc/init.d/ibmcloud
	$(INSTALL_CONF) ./files/ibmcloud.config $(1)/etc/config/ibmcloud
endef

$(eval $(call BuildPackage,ibmcloud))
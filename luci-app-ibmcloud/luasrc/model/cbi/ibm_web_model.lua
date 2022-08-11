map= Map("ibmcloud")

section = map:section(NamedSection, "ibmcloud_sct", "ibmcloud","IBM IoT cloud")

flag = section:option(Flag,"enable","Enable","Enables data transfer to IBM IoT cloud")

org_id = section:option( Value, "orgId", "Org_Id")

type_id = section:option( Value, "typeId", "Type_Id")

dev_id = section:option( Value, "deviceId", "Device_Id")

auth = section:option( Value, "auth_token", "Authenticator token")
auth.datatype = "string"
auth.maxlength = 50

return map
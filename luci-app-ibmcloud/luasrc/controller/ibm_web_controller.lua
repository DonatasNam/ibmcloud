module("luci.controller.ibm_web_controller",package.seeall)

function index()
    entry({"admin","services","ibmcloud"},cbi("ibm_web_model"),"IBM IoT cloud", 100)
end


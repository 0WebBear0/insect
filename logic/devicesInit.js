const devicesInit = require("../models/devices");

module.exports = async function deviceInit (req, res) {
    const uuidDevice = req.query.uuid

    let device = null

    try {
        if (uuidDevice) {
            device = await devicesInit.findOne({
                uuid: uuidDevice
            })
        }
        res.send(device)
    }
    catch (error) {
        res.send(error)
    }
}
const devices = require("../models/devices");

module.exports = async function deviceUpdateSettings (req, res) {
    const uuidDevice = req.query.uuid
    const newSettings = req.body

    let device = null

    try {
        if (uuidDevice) {
            device = await devices.update(
                {
                    selectedInsect: newSettings?.selectedInsect || null,
                    albedo: newSettings?.albedo || null,
                    height: newSettings?.height || null,
                },
                {uuid: uuidDevice})
        }
        res.send(device)
    }
    catch (error) {
        res.send(error)
    }
}
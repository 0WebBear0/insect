const insects = require("../models/insects");

module.exports = async function getAllInsects (req, res) {
    let device = null

    try {
        const allInsects = await insects.findAll()
        res.send(allInsects)
    }
    catch (error) {
        res.send(error)
    }
}
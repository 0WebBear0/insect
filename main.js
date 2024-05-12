const express = require('express')
const devices = require("./models/devices");
const e = require("express");

const app = express()

app.get('/', async function (req, res) {
    const uuidDevice = req.query.uuid

    let device = null

    try {
        const isFindDevice = await devices.findOne({
            where: {
                uuid: uuidDevice
            }
        })

        if (uuidDevice) {
            device = await devices.create({
                uuid: uuidDevice
            })
        }
    }
    catch (error) {
        console.log(error)
    }

    res.send(device)
})

app.listen(80)
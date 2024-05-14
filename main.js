const express = require('express')
const deviceInit = require('./logic/devicesInit')
const deviceUpdateSettings = require('./logic/deviceUpdateSettings')
const getAllInsects = require('./logic/getAllInsects')

const app = express()

app.get('/', deviceInit)
app.post('/change', deviceUpdateSettings)

app.get('/insects', getAllInsects)

app.listen(80)
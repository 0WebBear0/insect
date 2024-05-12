// Db
const { DataTypes} = require('sequelize')
const db = require('../infrastructure/db.js')

const devices = db.define('devices',
    // Описание таблиц
    {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true,
            allowNull: false
        },
        uuid: {
            type: DataTypes.STRING,
            allowNull: false
        },
    },
    // Опции
    {
        timestamps: false
    }
)

module.exports = devices
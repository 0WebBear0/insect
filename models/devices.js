// Db
const { DataTypes} = require('sequelize')
const db = require('../infrastructure/db.js')

const devices = db.define('devices',
    // Описание таблиц
    {
        uuid: {
            primaryKey: true,
            autoIncrement: true,
            type: DataTypes.UUIDV4,
            allowNull: false
        },
        selectedInsect: {
            type: DataTypes.BIGINT,
            allowNull: false
        },
        albedo: {
            type: DataTypes.REAL,
            allowNull: false
        },
        height: {
            type: DataTypes.REAL,
            allowNull: false
        },
    },
    // Опции
    {
        timestamps: false
    }
)

module.exports = devices
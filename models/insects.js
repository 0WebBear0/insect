// Db
const { DataTypes } = require('sequelize')
const db = require('../infrastructure/db')

const insects = db.define('insects',
    // Описание таблиц
    {
        // id, insectname, "wavelengthStart", "wavelengthEnd"
        id: {
            type: DataTypes.BIGINT,
            primaryKey: true,
            autoIncrement: true,
            allowNull: false
        },
        insectname: {
            type: DataTypes.STRING,
            allowNull: false
        },
        wavelengthStart: {
            type: DataTypes.BIGINT,
            allowNull: false
        },
        wavelengthEnd: {
            type: DataTypes.BIGINT,
            allowNull: false
        },
        wavelengthFavorite: {
            type: DataTypes.BIGINT,
            allowNull: false
        },
    },
    // Опции
    {
        timestamps: false
    }
)

module.exports = insects
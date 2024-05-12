// Db
const { DataTypes } = require('sequelize')
const {db} = require('../infrastructure/db')

const insects = db.define('insects',
    // Описание таблиц
    {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true,
            allowNull: false
        },
        wavelength: {
            type: DataTypes.STRING,
            allowNull: false
        },
    },
    // Опции
    {
        timestamps: false
    }
)

export default insects
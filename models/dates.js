// Db
const { DataTypes } = require('sequelize')
const {db} = require('../infrastructure/db')

const dates = db.define('dates',
    // Описание таблиц
    {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true,
            allowNull: false
        },
        data: {
            type: DataTypes.STRING,
            allowNull: false
        },
    },
    // Опции
    {
        timestamps: false
    }
)

export default dates
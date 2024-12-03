/**
 * @file thermostat.c
 * @brief Thermostat system with states for heating, cooling, and fan speed control.
 */

#include <stdbool.h>

/**
 * @brief Possible states of the thermostat.
 */
typedef enum {
    STATE_IDLE,    /**< Thermostat is idle. */
    STATE_HEATING, /**< Thermostat is heating. */
    STATE_COOLING  /**< Thermostat is cooling. */
} ThermostatState;

/**
 * @brief Fan speeds for the thermostat.
 */
typedef enum {
    FAN_LOW,    /**< Low fan speed. */
    FAN_MEDIUM, /**< Medium fan speed. */
    FAN_HIGH    /**< High fan speed. */
} FanSpeed;

/**
 * @brief Thermostat state variables.
 */
typedef struct {
    int currentTemp;       /**< Current temperature. */
    int targetTemp;        /**< Target temperature. */
    ThermostatState state; /**< Current state of the thermostat. */
    FanSpeed fanSpeed;     /**< Current fan speed. */
} Thermostat;

/**
 * @brief Initializes the thermostat to its default state.
 * @param thermostat Pointer to the thermostat state structure.
 */
void initThermostat(Thermostat *thermostat) {
    thermostat->currentTemp = 20;
    thermostat->targetTemp = 22;
    thermostat->state = STATE_IDLE;
    thermostat->fanSpeed = FAN_LOW;
}

/**
 * @brief Sets a new target temperature and adjusts the state and fan speed.
 * @param thermostat Pointer to the thermostat state structure.
 * @param newTarget New target temperature (must be between 16 and 30).
 */
void setTargetTemp(Thermostat *thermostat, int newTarget) {
    if (newTarget >= 16 && newTarget <= 30 && newTarget != thermostat->targetTemp) {
        thermostat->targetTemp = newTarget;
        if (newTarget > thermostat->currentTemp) {
            thermostat->state = STATE_HEATING;
            thermostat->fanSpeed = FAN_HIGH;
        } else if (newTarget < thermostat->currentTemp) {
            thermostat->state = STATE_COOLING;
            thermostat->fanSpeed = FAN_HIGH;
        } else {
            thermostat->state = STATE_IDLE;
            thermostat->fanSpeed = FAN_LOW;
        }
    }
}

/**
 * @brief Increases the current temperature during heating.
 * @param thermostat Pointer to the thermostat state structure.
 */
void increaseTemp(Thermostat *thermostat) {
    if (thermostat->state == STATE_HEATING && thermostat->currentTemp < thermostat->targetTemp) {
        thermostat->currentTemp++;
        if (thermostat->currentTemp == thermostat->targetTemp) {
            thermostat->state = STATE_IDLE;
            thermostat->fanSpeed = FAN_LOW;
        } else {
            thermostat->fanSpeed = FAN_MEDIUM;
        }
    }
}

/**
 * @brief Decreases the current temperature during cooling.
 * @param thermostat Pointer to the thermostat state structure.
 */
void decreaseTemp(Thermostat *thermostat) {
    if (thermostat->state == STATE_COOLING && thermostat->currentTemp > thermostat->targetTemp) {
        thermostat->currentTemp--;
        if (thermostat->currentTemp == thermostat->targetTemp) {
            thermostat->state = STATE_IDLE;
            thermostat->fanSpeed = FAN_LOW;
        } else {
            thermostat->fanSpeed = FAN_MEDIUM;
        }
    }
}

/**
 * @brief Maintains the thermostat state if no changes are needed.
 * @param thermostat Pointer to the thermostat state structure.
 */
void noChange(Thermostat *thermostat) {
    if (thermostat->currentTemp == thermostat->targetTemp) {
        thermostat->state = STATE_IDLE;
        thermostat->fanSpeed = FAN_LOW;
    }
}


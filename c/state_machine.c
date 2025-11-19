#include <stdio.h>

/*
*   Can be used to monitor sensor statuses. 

    - Use interrupt to check status of sensor (timer or event based)
    - In interrupt function, check if value goes over thresholds. If they do switch state on state machine else do nothing.
    - Only switch the state in the interrupt function! Call action function in main based on state of FSM

*/


typedef enum
{
    NORMAL,
    WARNING,
    ALARM
} sensor_states_t;

typedef enum
{
    SENSOR_OK,
    SENSOR_HIGH,
    SENSOR_CRITICAL
} sensor_events_t;

const char * state_names[] = {"NORMAL", "WARNING", "ALARM"};
const char * event_names[] = {"SENSOR_OK", "SENSOR_HIGH", "SENSOR_CRITICAL"};

typedef struct
{
    int sensor_value;
    sensor_states_t state;
    sensor_events_t event;
} sensor_t;

sensor_events_t check_sensor_status(int value)
{

    if(value > 50 && value < 90)
    {
        return SENSOR_HIGH;
    }
    if(value > 90)
    {
        return SENSOR_CRITICAL;
    }

    return SENSOR_OK;
}

sensor_states_t fsm_update(sensor_states_t state, sensor_events_t event)
{
    switch (state)
    {
        case NORMAL:
            if(event == SENSOR_HIGH)
            {
                return WARNING;
            }
            if(event == SENSOR_CRITICAL)
            {
                return ALARM;
            }
            break;
        case WARNING:
            if(event == SENSOR_CRITICAL)
            {
                return ALARM;
            }
            if(event == SENSOR_OK)
            {
                return NORMAL;
            }
            break;
        case ALARM:
            if(event == SENSOR_OK)
            {
                return NORMAL;
            }
            if(event == SENSOR_HIGH)
            {
                return WARNING;
            }
            break;
    }

    return state;
}

int main()
{
    sensor_t temp_sensor = {10, SENSOR_OK, NORMAL};

    while(1)
    {
        scanf("%d", &temp_sensor.sensor_value);
        temp_sensor.event = check_sensor_status(temp_sensor.sensor_value);
        temp_sensor.state = fsm_update(temp_sensor.state, temp_sensor.event);
        printf("Current state: %s\nCurrent event: %s\n", state_names[temp_sensor.state], event_names[temp_sensor.event]);
    }

    return 0;
}
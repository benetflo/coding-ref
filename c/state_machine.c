#include <stdio.h>

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
    int current_sensor_value = 10;
    sensor_events_t current_event = SENSOR_OK;
    sensor_states_t current_state = NORMAL;

    while(1)
    {
        scanf("%d", &current_sensor_value);
        current_event = check_sensor_status(current_sensor_value);
        current_state = fsm_update(current_state, current_event);
        printf("Current state: %d\nCurrent event: %d\n", current_state, current_event);
    }


    return 0;
}
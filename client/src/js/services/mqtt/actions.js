export function initMqttConnection(){
    return {
        type: 'INIT_MQTT_CONNECTION',
    }
}

export function mqttPublish(topic, message){
    return {
        type: 'MQTT_PUBLISH',
        topic: topic,
        payload: message
    }
}
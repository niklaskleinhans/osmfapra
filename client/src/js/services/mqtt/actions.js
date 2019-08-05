export function initMqttConnection(actionTopicMapping){
    return {
        type: 'INIT_MQTT_CONNECTION',
        payload:{actionTopicMapping: actionTopicMapping}
    }
}

export function mqttPublish(topic, message){
    return {
        type: 'MQTT_PUBLISH',
        topic: topic,
        payload: message
    }
}

export function generateShareLinkListener(sharelinkkey){
    return {
        type: 'GENERATE_SHARE_LINK_LISTENER',
        payload: sharelinkkey
    }
}
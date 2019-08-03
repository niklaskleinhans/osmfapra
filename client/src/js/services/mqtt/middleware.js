import { createClient} from '../../lib/mqttredux'
import * as coreActions from '../core/actions'

const mqttConfig = {
    url: 'ws://192.168.1.21:15675/ws',
    opt: {
      clientId: 'osm-' + Date.now(),
      protocolId: 'MQIsdp',
      protocolVersion: 3,
    },
  };
  const mqttRedux = createClient(mqttConfig);
  const actionTopicMapping = {};
  
  
  

const mqttMiddleware = (function(){
    return store => next => action => {
        switch (action.type) {
            case 'INIT_MQTT_CONNECTION':
                mqttRedux.connect(actionTopicMapping, store);
                next(action)
                break;
            case 'MQTT_CONNECTED':
                coreActions.createNotification({content: action.message, type: 'good'}) 
                break;
            case 'MQTT_PUBLISH':
                mqttRedux.publish(action.topic, action.payload)
            default:
                return next(action)
        }
    }
})();

export default mqttMiddleware
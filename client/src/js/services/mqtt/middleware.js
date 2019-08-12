import { createClient} from '../../lib/mqttredux'
import * as coreActions from '../core/actions'
import * as mapActions from '../map/actions'

const mqttConfig = {
    //url: 'ws://192.168.1.21:15675/ws',
    url: 'wss://192.168.1.21:15673/ws',
    opt: {
      clientId: 'osm-' + Date.now(),
      protocolId: 'MQIsdp',
      protocolVersion: 3,
    },
  };
  const mqttRedux = createClient(mqttConfig);
  
  
  

const mqttMiddleware = (function(){
    return store => next => action => {
        switch (action.type) {
            case 'INIT_MQTT_CONNECTION':
                mqttRedux.connect(action.payload.actionTopicMapping, store);
                next(action)
                break;
            case 'MQTT_CONNECTED':
                store.dispatch(coreActions.createNotification({content: action.message, type: 'good'}))
                break;
            case 'MQTT_PUBLISH':
                mqttRedux.publish(action.topic, action.payload)
                next(action)
                break;
            case 'MQTT_ERROR':
                store.dispatch(coreActions.createNotification({content: action.error, type: 'bad'}))
                next(action)
                break;
            case 'RECEIVE_COORDINATES':
                //store.dispatch(coreActions.createNotification({content:action.payload, type:'good'}))
                store.dispatch(mapActions.updateCoordinatesFriend(JSON.parse(action.payload)))
                store.dispatch(coreActions.getRouteByCoordinate())
                next(action)
                break;
            case 'GENERATE_SHARE_LINK_LISTENER':
                //console.log('client/coordinates/' + action.payload)
                mqttRedux.subscribe({'RECEIVE_COORDINATES': 'client/coordinates/' + action.payload})
                next(action)
                break;
            default:
                return next(action)
        }
    }
})();

export default mqttMiddleware
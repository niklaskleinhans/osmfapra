import * as mqttActions from '../mqtt/actions'
import * as coreActions from '../core/actions'
import * as helpers from '../../helpers'

const mapMiddleware = (function(){
    return store => next => action => {
        switch (action.type) {

            case 'UPDATE_COORDINATES_FRIEND':
                if (!store.getState().map.friendCoordinates){
                    store.dispatch(coreActions.createNotification({content: "Friend is Connected", type: 'info'}))
                }
                next(action)
                break;
            
            case 'GET_CURRENT_LOCATION':
                navigator.geolocation.getCurrentPosition(position => {
                    action.position = position;
                    next(action)
                },
                error => alert(error.message));
                break;
            
            case 'SEND_LOCATION':
                navigator.geolocation.getCurrentPosition(position => {
                    var coordinates = {'position': [position.coords.latitude, position.coords.longitude]}
                    store.dispatch(mqttActions.mqttPublish('client/coordinates', JSON.stringify(coordinates)))
                },
                error => alert(error.message));
                next(action)
                break;
            case 'UPDATE_COORDINATES_FRIEND':
                if(store.getState().map.friendCoordinates){
                    // check if the new friend is less then 5km away from old position. Instead ins an unrealistic update
                    if(helpers.pointDistance(action.payload.position, store.getState().map.friendCoordinates)> 5000){
                        action.payload.position=store.getState().map.friendCoordinates
                    }
                }
                next(action)
                break
            
            default:
                return next(action)
        }
    }
})();

export default mapMiddleware
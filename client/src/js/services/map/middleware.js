import * as mqttActions from '../mqtt/actions'

const mapMiddleware = (function(){
    return store => next => action => {
        switch (action.type) {
            
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
            
            default:
                return next(action)
        }
    }
})();

export default mapMiddleware
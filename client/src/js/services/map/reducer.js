export default function reducer(map = {}, action){
    switch(action.type){
        case 'UPDATE_COORDINATES_FRIEND':
            return Object.assign({}, map, { friendCoordinates: action.payload.position });
        case 'GET_CURRENT_LOCATION':
            var position = [action.position.coords.latitude, action.position.coords.longitude]
            return Object.assign({}, map, { currentCoordinates: position });
        case 'STORE_ROUTE':
            return Object.assign({}, map, {route : action.payload})
        default:
            return map;
    }
}
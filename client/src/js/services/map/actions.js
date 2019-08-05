export function updateCoordinatesFriend(coordinates){
    return {
        type: 'UPDATE_COORDINATES_FRIEND',
        payload: coordinates
    }
}

export function getCurrentLocation(){
    return{
        type: "GET_CURRENT_LOCATION"
    }
}

export function sendLocation(){
    return{
        type: "SEND_LOCATION"
    }
}
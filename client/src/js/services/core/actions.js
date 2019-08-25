/*internal Functions */
function fillNotification(data){
    var notification = Object.assign(
        {
            key: new Date().valueOf().toString(),
            duration: 5,
            type: 'default',
            title: null,
            content: null,
            description: null,
            sticky: false,
            closing: false
        })

   if (typeof data.title !== 'undefined' ) notification.title = data.title
   if (typeof data.content !== 'undefined' ) notification.content = data.content
   if (typeof data.description !== 'undefined' ) notification.description = data.description
   if (typeof data.sticky !== 'undefined' ) notification.sticky = data.sticky
   if (typeof data.closing !== 'undefined' ) notification.closing = data.closing
   if (typeof data.type !== 'undefined') notification.type = data.type
   //console.log(notification)
    
   return notification
}

/* Init Stuff */

export function initConfigurations(epsilonDistancePath, epsilonDistanceMax){
    var config = {
        epsilonDistancePath : epsilonDistancePath,
        epsilonDistanceMax : epsilonDistanceMax
    }
    return {
        type: 'INIT_CONFIGURATIONS',
        payload: config
    }
}


/* UI Stuff */
export function toggleSidebar(new_state = 'toggle') {
    var action = {
        type: 'TOGGLE_SIDEBAR'
    }
    if (new_state != 'toggle'){
        action.new_state = new_state
    }
    return action
}



/* Noficiations stuff */
export function createNotification(data){
    return {
        type: 'CREATE_NOTIFICATION',
        notification: fillNotification(data)
    }
}
export function closeNotification(key){
    return { 
        type: 'CLOSE_NOTIFICATION',
        key: key
    }
}

export function removeNotification(key, manual = false){
    return { 
        type: 'REMOVE_NOTIFICATION',
        key: key,
        manual: manual
    }
}

/* Routing stuff */
export function generateShareLink(){
    return {
        type: 'GENERATE_SHARE_LINK'
    }
}

export function getRouteByCoordinate(){
    return {
        type: 'GET_ROUTE_BY_COORDINATE'
    }
}


export default function reducer(core = {}, action){
    switch(action.type){
        case 'SET_NAME':
            return Object.assign({}, core, {name: action.payload});
        case 'TOGGLE_SIDEBAR':
                var new_state = !core.sidebar_open
                if (typeof(action.new_state) !== 'undefined' ) new_state = action.new_state
                return Object.assign({}, core, { sidebar_open : new_state })
        case 'CREATE_NOTIFICATION':
            var notifications = Object.assign({}, core.notifications);
            notifications[action.notification.key] = action.notification;
            return Object.assign({}, core, { notifications: notifications });
        case 'CLOSE_NOTIFICATION':
            var notifications = Object.assign({}, core.notifications);
            if (notifications[action.key]){
                notifications[action.key].closing = true;
            }
            return Object.assign({}, core, { notifications: notifications });
        case 'REMOVE_NOTIFICATION':
            var notifications = Object.assign({}, core.notifications);
            delete notifications[action.key];
            return Object.assign({}, core, {notifications: notifications});
        case 'GENERATE_SHARE_LINK':
            return Object.assign({}, core, {sharelink: action.sharelink})
        case 'GET_ROUTE_BY_COORDINATE':
            return Object.assign({}, core, {routeonrequest: action.routeonrequest})
        default:
            return core;
    }
}